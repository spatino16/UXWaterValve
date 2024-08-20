/**
 * @file
 * Handler for Command Class Meter.
 * @copyright 2023 Trident IOT
 * @author Brandon G.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include "ZAF_types.h"
#include "ZW_TransportEndpoint.h"
#include "ZW_TransportSecProtocol.h"
#include "ZAF_Common_interface.h"
#include "zaf_transport_tx.h"
#include "zaf_config_api.h"
#include "zpal_misc.h"
#include <stdbool.h>
#include <stdint.h>
#include "CC_Meter.h"

#define DEBUGPRINT
#include "DebugPrint.h"
/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/


/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

// Nothing here.

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

// Nothing here.

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/
static received_frame_status_t
CC_Meter_handler(
		cc_handler_input_t * pInput,
		cc_handler_output_t * pOutput
);

size_t cc_meter_construct_meterReport(uint8_t* p_frame, cc_meter_meterType_t meter_type, cc_meter_rateType_t rate_type, cc_meter_scale_t scale, uint8_t precision, uint8_t size, uint32_t currentValue, uint32_t lastValue, uint16_t deltaTimeSeconds);

size_t cc_meter_construct_meterSupportedReport(uint8_t* p_frame, cc_meter_meterType_t meterType, cc_meter_rateType_t rateType, bool meterReset, cc_meter_scale_bitMask_t supportedScalesBitmask );

size_t cc_meter_construct_meterReport(uint8_t* p_frame, cc_meter_meterType_t meter_type, cc_meter_rateType_t rate_type, cc_meter_scale_t scale, uint8_t precision, uint8_t size, uint32_t currentValue, uint32_t lastValue, uint16_t deltaTimeSeconds)
{
	DPRINTF("\r\n\tMeter Report> type:%02X, rate:%02X, scale:%02X, prec.:%d, size:%d, current:%X, last:%X, delta:%X", meter_type, rate_type, scale, precision, size, currentValue, lastValue, deltaTimeSeconds);
    if( NULL == p_frame || size < 1)
        return 0;

    size_t frame_index = 0;

    p_frame[frame_index++] = COMMAND_CLASS_METER_V6;    //cmdClass
    p_frame[frame_index++] = METER_REPORT_V6;           //cmd

    p_frame[frame_index] = 0;                         //Properties 1

    p_frame[frame_index] |= METER_REPORT_PROPERTIES1_METER_TYPE_MASK_V6 & meter_type;
    p_frame[frame_index] |= METER_REPORT_PROPERTIES1_RATE_TYPE_MASK_V6 & (rate_type << METER_GET_PROPERTIES1_RATE_TYPE_SHIFT_V6);

    /* The scale is encoded into potentially 3 different bytes very strangely... a single bit is in properites1 and  3 bits are in properties2, and there is an additional field appended to the message if the value of the scale is >= 7 */

    uint8_t scale1;
    uint8_t scale2;
    bool scale2_used;

    if( scale >= 0x07 )
    {
        scale1 = 0x07;
        scale2 = scale - 0x07;
        scale2_used = true;
    }
    else
    {
        scale1 = scale;
        scale2 = 0;
        scale2_used = false;
    }

    /* bit 2 of the scale is in the properties1 bit 7... */
    if( scale1 & (1 << 2) )
        p_frame[frame_index] |= METER_REPORT_PROPERTIES1_SCALE_BIT_2_BIT_MASK_V6;

    frame_index++;//properties2

    p_frame[frame_index] = 0;
    /* bit's 0, 1 of the scale are in bits 3 and 4 of properties 2... */
    p_frame[frame_index] |= METER_REPORT_PROPERTIES2_SCALE_BITS_10_MASK_V6 & (scale1 << METER_RESET_PROPERTIES2_SCALE_BITS_10_SHIFT_V6);

    /* size field in properties 2 */
    p_frame[frame_index] |= METER_REPORT_PROPERTIES2_SIZE_MASK_V6 & size;

    /* precision field in properties 2 */
    p_frame[frame_index] |= METER_RESET_PROPERTIES2_PRECISION_MASK_V6 & (precision << METER_RESET_PROPERTIES2_PRECISION_SHIFT_V6);

    frame_index++;//Meter Value 1 MSB
    //copy up to 4 bytes for meter value 1 as big endian in the frame
    for(uint8_t i = 0; i < size && i < sizeof(uint32_t); ++i)
    {
        p_frame[frame_index++] = 0xFF & currentValue >>(8 * (size - (i+1)));
    }

    /* 16-bit Delta Time integer in seconds */
    p_frame[frame_index++] = 0xFF & (deltaTimeSeconds >> 8);//Delta time MSB
    p_frame[frame_index++] = 0xFF & (deltaTimeSeconds);     //Delta time LSB

    if( 0 < deltaTimeSeconds )
    {
        /* if we are to include the last value, then write it to the frame as well. */
        for(uint8_t i = 0; i < size && i < sizeof(uint32_t); ++i)
        {
            p_frame[frame_index++] = 0xFF & lastValue >>(8 * (size - (i+1)));
        }
    }

    /* Append the MSB of the scale to the end of the message only if the LSB is 0x07... Who thought of this?! */
    if( scale2_used )
    {
        p_frame[frame_index++] = scale2;
    }

    return frame_index;
}

static int8_t get_next_index_of_bit_set(cc_meter_scale_bitMask_t bitMask, int8_t lastBitIndex) {
    // Move to the next bit position
    lastBitIndex++;

    // Find the next set bit from the updated lastBitIndex position
    for (; lastBitIndex < (int8_t)sizeof(cc_meter_scale_bitMask_t); lastBitIndex++) {
        if (bitMask & (1U << lastBitIndex)) {
            return lastBitIndex;
        }
    }

    // No more bits set in the bitMask
    return -1;
}

static cc_meter_scale_t bit_index_to_scale_value(int8_t lastBitIndex)
{
    return (cc_meter_scale_t)lastBitIndex + 1;
}




size_t cc_meter_construct_meterSupportedReport(uint8_t* p_frame, cc_meter_meterType_t meterType, cc_meter_rateType_t rateType, bool meterReset, cc_meter_scale_bitMask_t supportedScalesBitmask )
{

    size_t frame_index = 0;

    if( NULL == p_frame )
        return frame_index;

    p_frame[frame_index++] = COMMAND_CLASS_METER_V6;
    p_frame[frame_index++] = METER_SUPPORTED_REPORT_V6;

    /* Properties 1 */
    p_frame[frame_index] = 0;

    /* Properties 1: Meter Reset Field */
    if( meterReset )
        p_frame[frame_index] |= METER_SUPPORTED_REPORT_PROPERTIES1_METER_RESET_BIT_MASK_V6;

    /* Properties 1: Rate Type Field */
    p_frame[frame_index] |= METER_SUPPORTED_REPORT_PROPERTIES1_RATE_TYPE_MASK_V6 & (rateType << METER_SUPPORTED_REPORT_PROPERTIES1_RATE_TYPE_SHIFT_V6);

    /* Properties 1: Meter Type Field */
    p_frame[frame_index] |= METER_SUPPORTED_REPORT_PROPERTIES1_METER_TYPE_MASK_V6 & meterType;

    /* Properties 2 */
    frame_index++;
    p_frame[frame_index] = 0;

    uint8_t numberOfScalesSupported = 0;
    for(cc_meter_scale_bitMask_t mask = 1; mask != 0; mask <<= 1)
    {
        if( 0 != ( mask & supportedScalesBitmask ) )
            numberOfScalesSupported++;
    }

    /* Properties 2: Scale Supported Byte 1 */
    if( numberOfScalesSupported < 1 )
        return frame_index + 1;

    /* Get first scale value */
    int8_t scaleIndex = get_next_index_of_bit_set(supportedScalesBitmask, -1);

    /* First scale is in properties 2 */
    p_frame[frame_index] |= METER_SUPPORTED_REPORT_PROPERTIES2_SCALE_SUPPORTED_0_MASK_V6 & bit_index_to_scale_value(scaleIndex);

    numberOfScalesSupported--;

    if( numberOfScalesSupported < 1 )
        return frame_index + 1;
    /* Properties 2: MST field set if there are additional fields */
    p_frame[frame_index++] |= METER_SUPPORTED_REPORT_PROPERTIES2_M_S_T_BIT_MASK_V6;

    /* The number of scales supported bit-mask bytes following */
    p_frame[frame_index++] = numberOfScalesSupported;

    for(cc_meter_scale_bitMask_t mask = 1; mask != 0; mask <<= 1)
    {

        /* Append the rest of the itmask bytes */
        for(size_t i = 0; i < numberOfScalesSupported; ++i)
        {
            scaleIndex = get_next_index_of_bit_set(supportedScalesBitmask, scaleIndex);

            p_frame[frame_index++] = bit_index_to_scale_value(scaleIndex);
        }
    }

    return frame_index;
}




bool
cc_meter_meterReport_tx(
  const agi_profile_t* pProfile,
  uint8_t sourceEndpoint,
  cc_meter_scale_t scale,
  cc_meter_rateType_t rateType,
  VOID_CALLBACKFUNC(pCbFunc)(TRANSMISSION_RESULT * pTransmissionResult))
{
    ZW_APPLICATION_TX_BUFFER txBuf;

    uint32_t currentValue = 0;
    uint32_t lastValue = 0;
    uint8_t numBytes = 0;
    uint16_t deltaTimeSeconds = 0;
    uint8_t precision = 0;


    cc_meter_meterInfo_t* p_meterInfo = NULL;

    /* Look up meter by endpoint */
    bool validEndpoint = cc_meter_get_meterInfo(
        sourceEndpoint,
        &p_meterInfo
    );

    if(false == validEndpoint || NULL == p_meterInfo)
    {

        return false;
    }

    numBytes = cc_meter_handle_get_meter_value(sourceEndpoint, rateType, scale, &precision, &currentValue, &lastValue, &deltaTimeSeconds);

    if( numBytes < 1 )
    {
        /* Scale not supported */
        return false;
    }

    uint8_t lengthOfFrame = 0xFF & cc_meter_construct_meterReport((uint8_t*)&(txBuf), p_meterInfo->meterType, rateType, scale, precision, numBytes, currentValue, lastValue, deltaTimeSeconds);

    if( lengthOfFrame < 1 )
    {
        /* Something wrong with the meterType, rateType, or scale */
        return false;
    }

    zaf_tx_options_t tx_options = { 0 };
    tx_options.dest_node_id = 0;
    tx_options.agi_profile = pProfile;
    tx_options.source_endpoint = sourceEndpoint;

    /* Use supervision encapsulation if using S2 */
    switch( GetHighestSecureLevel( ZAF_GetSecurityKeys() ) ){
        case SECURITY_KEY_NONE:
        case SECURITY_KEY_S0:
            tx_options.use_supervision = false;
            break;
        case SECURITY_KEY_S2_UNAUTHENTICATED:
        case SECURITY_KEY_S2_AUTHENTICATED:
        case SECURITY_KEY_S2_ACCESS:
        default:
            tx_options.use_supervision = true;

    }

     return zaf_transport_tx((uint8_t *)&txBuf, lengthOfFrame, pCbFunc, &tx_options);
}


static received_frame_status_t
CC_Meter_handler(
		cc_handler_input_t * pInput,
		cc_handler_output_t * pOutput
)
{
    bool responseExpected = false;
    cc_meter_meterInfo_t* p_meterInfo = NULL;

    /* Look up meter by endpoint */
    bool validEndpoint = cc_meter_get_meterInfo(
		pInput->rx_options->destNode.endpoint,
        &p_meterInfo
    );

    DPRINT("\r\n[CC METER]");

    if( false == validEndpoint || NULL == p_meterInfo )
    {
    	DPRINTF( "No meter associated with Endpoint:%d", pInput->rx_options->destNode.endpoint );
        return RECEIVED_FRAME_STATUS_FAIL;
    }

    /* Add to this any commands which are not allowed to respond if received using end points or multicast */
    switch( pInput->frame->ZW_Common.cmd )
    {
        // None of the following commands support end point bit addressing.
        case METER_GET_V6:
        case METER_SUPPORTED_GET_V6:
        {
            if (true == Check_not_legal_response_job(pInput->rx_options))
            {
              return RECEIVED_FRAME_STATUS_FAIL;
            }
            DPRINT(" response expected...");
            responseExpected = true;

        }break;

        default:
            /* Assuming all other commands are ok */
        	DPRINT(" response not expected...");
            break;
    }



    switch( pInput->frame->ZW_Common.cmd )
    {
        case METER_GET_V6:
        {
            uint32_t currentValue = 0;
            uint32_t lastValue = 0;
            uint8_t numBytes = 0;
            uint16_t deltaTimeSeconds = 0;
            cc_meter_rateType_t rateType = cc_meter_rateType_Unspecified;
            uint8_t precision = 0;

            cc_meter_scale_t scale = 0;

            if( pInput->length <= sizeof(ZW_METER_GET_FRAME) )
            {
                /* Contains no fields */
            }
            else if( pInput->length <= sizeof(ZW_METER_GET_V4_FRAME) )
            {
                /* Contains only a 3-bit scale */
                scale = (METER_GET_PROPERTIES1_SCALE_MASK_V6 & pInput->frame->ZW_MeterGetV6Frame.properties1) >> METER_GET_PROPERTIES1_SCALE_SHIFT_V6;
            }
            else
            {

                /* Contains a 3-bit OR 8-bit scale */
            	cc_meter_scale_t scale1 = (METER_GET_PROPERTIES1_SCALE_MASK_V6 & pInput->frame->ZW_MeterGetV6Frame.properties1) >> METER_GET_PROPERTIES1_SCALE_SHIFT_V6;

                if( scale1 == 0x07 )
                {
                    scale = 0x07 + pInput->frame->ZW_MeterGetV6Frame.scale2;
                }

                /* May also contain a Rate Type */
                rateType = (METER_GET_PROPERTIES1_RATE_TYPE_MASK_V6 & pInput->frame->ZW_MeterGetV6Frame.properties1) >> METER_GET_PROPERTIES1_RATE_TYPE_SHIFT_V6;

            }

            /* The default scale will be used if one is not specified except 0 is a valid scale, so you cannot support a scale=0 AND have a default which is not zero... That's the way this logic is to match the AWG spec. */
			if( 0 == scale )
			{
				scale = p_meterInfo->default_scale;
			}

            numBytes = cc_meter_handle_get_meter_value(pInput->rx_options->destNode.endpoint, rateType, scale, &precision, &currentValue, &lastValue, &deltaTimeSeconds);

            if( numBytes < 1 )
            {
                /* Scale not supported */
                return RECEIVED_FRAME_STATUS_FAIL;
            }

            pOutput->length = 0xFF & cc_meter_construct_meterReport((uint8_t*)&pOutput->frame->ZW_Common.cmdClass, p_meterInfo->meterType, rateType, scale, precision, numBytes, currentValue, lastValue, deltaTimeSeconds);

            /* Save last value comunicated and when it was reported, so we can calculated the delta in the report. */
            cc_meter_report_completed(pInput->rx_options->destNode.endpoint, scale, rateType);

        }break;

        case METER_SUPPORTED_GET_V6:
        {

        	pOutput->length = 0xFF & cc_meter_construct_meterSupportedReport((uint8_t*)&pOutput->frame->ZW_Common.cmdClass, p_meterInfo->meterType, p_meterInfo->rateTypeSupported, p_meterInfo->resettable, p_meterInfo->scalesSupportedBitMask );


        }break;


        case METER_RESET_V6:
        {
            /* Check if meter reset is supported */
            if( false == p_meterInfo->resettable )
                return RECEIVED_FRAME_STATUS_NO_SUPPORT;

            if( pInput->length <= sizeof(ZW_METER_RESET_V5_FRAME) )
            {
                /* Older versions of this command only have the first two bytes, so just reset to zero. */
                cc_meter_handle_reset_cmd(pInput->rx_options->destNode.endpoint, 0, 0, 0, 0, 0);
            }
            else if( pInput->length >= sizeof(ZW_METER_RESET_1BYTE_V6_FRAME) )
            {
                /* Newer versions have additional fields to know what to reset the meter to */
                cc_meter_rateType_t rateType = (pInput->frame->ZW_MeterReset1byteV6Frame.properties1 & METER_RESET_PROPERTIES1_RATE_TYPE_MASK_V6) >> METER_RESET_PROPERTIES1_RATE_TYPE_SHIFT_V6;
                //cc_meter_meterType_t meterType = pFrameIn->ZW_MeterReset1byteV6Frame.properties1 & METER_RESET_PROPERTIES1_METER_TYPE_MASK_V6;

                cc_meter_scale_t scale = 0;

                uint8_t precision = 0;

                uint8_t size = 0;

                uint32_t value = 0;

                /* Bit 2 of the scale is in bit 7 of properties1...*/
                if( 0 != (pInput->frame->ZW_MeterReset1byteV6Frame.properties1 & METER_RESET_PROPERTIES1_SCALE_BIT_2_BIT_MASK_V6) )
                    scale |= 1 << 2;

                precision = (pInput->frame->ZW_MeterReset1byteV6Frame.properties2 & METER_RESET_PROPERTIES2_PRECISION_MASK_V6) >> METER_RESET_PROPERTIES2_PRECISION_SHIFT_V6;

                scale |= (pInput->frame->ZW_MeterReset1byteV6Frame.properties2 & METER_RESET_PROPERTIES2_SCALE_BITS_10_MASK_V6) >> METER_RESET_PROPERTIES2_SCALE_BITS_10_SHIFT_V6;

                size = pInput->frame->ZW_MeterReset1byteV6Frame.properties2 & METER_RESET_PROPERTIES2_SIZE_MASK_V6;


                uint8_t * pValueField = &pInput->frame->ZW_MeterReset1byteV6Frame.meterValue1;

                /* Check value length. Must be 1, 2, or 4 */
                switch( size )
                {
                    case 1:
                    case 2:
                    case 4:
                        break;
                    default:
                        return RECEIVED_FRAME_STATUS_FAIL;
                }

                for(uint8_t i = 0; i < size; ++i)
                {
                    value >>= 8;
                    value |= pValueField[i];
                }

                bool resetOk = cc_meter_handle_reset_cmd(pInput->rx_options->destNode.endpoint, rateType, scale, precision, size, value);

                if( false == resetOk )
                {
                    /* Meter type, rate type, scale or something else is the wrong value. */
                    return RECEIVED_FRAME_STATUS_FAIL;
                }

            }
            else
            {
                /* bad frame length */
                return RECEIVED_FRAME_STATUS_FAIL;
            }

        }break;


        default:
        {
            return RECEIVED_FRAME_STATUS_NO_SUPPORT;
        }
    }


    /* If we expected a response, but didn't fill the response buffer, then return a failure status. */
    if( responseExpected )
    {
        if( pOutput->length < 1 )
        {
            return RECEIVED_FRAME_STATUS_FAIL;
        }
    }


    return RECEIVED_FRAME_STATUS_SUCCESS;
}






/* Add one command pair to the lifeline */
static uint8_t cc_meter_lifeline_report_get(cc_group_t * p_cc_pair)
{
    p_cc_pair->cmd = METER_REPORT_V6;
    p_cc_pair->cmdClass = COMMAND_CLASS_METER_V6;
    return 1;
}



#ifdef CC_METER_CFG_BASIC_MAPPED_TO_METER_CC

/**
 * CC Meter Basic Set mapper function type.
 *
 * Use this type when defining a function for Basic Set mapping.
 * @param[out] p_frame The frame that must have command class and command replaced by the command
 *                     class that defines the Basic Set mapping function.
 */
extern void cc_meter_basic_get_mapper(ZW_APPLICATION_TX_BUFFER * p_frame);


/**
 * CC Meter Basic Get mapper function type.
 *
 *
 *
 * Use this type when defining a function for Basic Get mapping.
 * @param[in]  endpoint        The endpoint that received the Basic Get command.
 * @param[out] p_current_value Pointer to variable where the current value can be written.
 * @param[out] p_target_value  Pointer to variable where the target value can be written.
 * @param[out] p_duration      Pointer to variable where the duration can be written.
 */
extern void cc_meter_basic_set_mapper(uint8_t endpoint, uint8_t * p_current_value, uint8_t * p_target_value, uint8_t * p_duration);


REGISTER_CC_V5(COMMAND_CLASS_METER_V6, METER_VERSION_V6, CC_Meter_handler, cc_meter_basic_set_mapper, cc_meter_basic_get_mapper, cc_meter_lifeline_report_get, 0, cc_meter_init_cb, cc_meter_reset_cb);

#else

REGISTER_CC_V5(COMMAND_CLASS_METER_V6, METER_VERSION_V6, CC_Meter_handler, NULL, NULL, cc_meter_lifeline_report_get, 0, cc_meter_init_cb, cc_meter_app_factory_reset);
#endif

