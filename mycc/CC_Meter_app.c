/*
 * CC_Meter_app.c
 *
 *  Created on: Jul 8, 2024
 *      Author: brandongruber
 */


#include "CC_Meter.h"
#include "CC_Meter_Types.h"
#include <freertos_os2.h>
#include <AppTimer.h>

#include <ZW_TransportEndpoint.h>

#define DEBUGPRINT
#include "DebugPrint.h"

#include "CC_Meter_app.h"
#include "cmsis_os2.h"

void cc_meter_app_auto_report_timer(SSwTimer* pTimer);



cc_meter_meterInfo_t meters[CC_METER_NUM_ENDPOINTS];


typedef struct{

     uint8_t precision;
     uint32_t value_actual;//Holds running total
     uint32_t value_reported;//Holds last value that was sent
     uint32_t value_reportedConfirmedReceived;//Holds the last value that was sent and confirmed to be received.
     uint8_t size;
     uint32_t timestampOfLastReport;
}gAppMeterValue_t;

typedef struct{
	cc_meter_scale_t scale;
	gAppMeterValue_t consumedIn;
	gAppMeterValue_t producedOut;
}gAppMeterData_t;

gAppMeterData_t meterScaleData[CC_METER_NUM_ENDPOINTS][CC_METER_NUM_METER_SCALES];

SSwTimer meter_auto_report_timer;

static uint32_t cc_meter_app_get_scale_index(uint8_t endpoint, cc_meter_scale_t scale);
static uint32_t cc_meter_app_get_scale_index(uint8_t endpoint, cc_meter_scale_t scale)
{
	(void)endpoint;
	(void)scale;
	/* this application only has one scale on one endpoint */
	return CC_METER_APP_SCALE_INDEX_GALLONS;
}


size_t cc_meter_app_init(cc_meter_meterInfo_t ** pp_meterInfo)
{
    *pp_meterInfo = (cc_meter_meterInfo_t *)&meters[0];

    /* in this example we have only one end point (the root) which is an electric meter with 4 separate scales */

    /* Clear meter scale values to zero */
    memset(&meterScaleData, 0, sizeof(meterScaleData));

    /* Initialize meter values either to zero or from nvm */
    meters[CC_METER_WATER_ENDPOINT].meterType     = cc_meter_MeterType_Water;
	meters[CC_METER_WATER_ENDPOINT].default_scale = cc_meter_scale_Water_USGallons;
	meters[CC_METER_WATER_ENDPOINT].rateTypeDefault = cc_meter_rateType_Import_Consumed;
	meters[CC_METER_WATER_ENDPOINT].rateTypeSupported = cc_meter_rateType_Import_Consumed;
	/* Water meter does not support being reset */
	meters[CC_METER_WATER_ENDPOINT].resettable    = false;
	/* Add all supported scales as a bitmask */
	meters[CC_METER_WATER_ENDPOINT].scalesSupportedBitMask = cc_meter_scale_to_bit_mask(cc_meter_scale_Water_USGallons);

    /* Init gallons consumed in */
	meterScaleData[CC_METER_WATER_ENDPOINT][CC_METER_APP_SCALE_INDEX_GALLONS].scale = cc_meter_scale_Water_USGallons;
    meterScaleData[CC_METER_WATER_ENDPOINT][CC_METER_APP_SCALE_INDEX_GALLONS].consumedIn.precision = CC_METER_APP_GALLONS_PRECISION;
    meterScaleData[CC_METER_WATER_ENDPOINT][CC_METER_APP_SCALE_INDEX_GALLONS].consumedIn.size = CC_METER_APP_GALLONS_SIZE;

    /* Optionally have this device report regularly it's usage. Note: only report regularly using a software timer that doesn't use interrupts. */
    AppTimerRegister(
        &meter_auto_report_timer,
        true,
        cc_meter_app_auto_report_timer
    );


    return CC_METER_NUM_ENDPOINTS;
}

static uint32_t cc_meter_time_delta_in_ticks( uint32_t currentTimeTicks, uint32_t savedTimeStamp )
{
	if( currentTimeTicks >= savedTimeStamp )
	{
		return currentTimeTicks - savedTimeStamp;
	}

	return (UINT32_MAX - savedTimeStamp + 1) + currentTimeTicks;
}



size_t cc_meter_handle_get_meter_value( uint8_t endpoint, cc_meter_rateType_t rateType, cc_meter_scale_t scale, uint8_t* p_precision, uint32_t* p_currentValue, uint32_t *p_lastValue, uint16_t* p_deltaTimeSeconds)
{
	DPRINTF("\r\n[CC METER APP]%s> ep:%d rate:%02X, scale:%02X", __func__, endpoint, rateType, scale );

    if( endpoint >= CC_METER_NUM_ENDPOINTS )
      return 0;

    if( cc_meter_rateType_Unspecified == rateType )
	{
		/* Set to default rate if one is not specified. */
    	DPRINTF("...rate to default:%02X", meters[endpoint].rateTypeDefault);
		rateType = meters[endpoint].rateTypeDefault;
	}

    /* Search through each scale at the end point for a matching meter */
	for(size_t scale_index = 0; scale_index < CC_METER_NUM_METER_SCALES; ++scale_index)
	{
		if( scale == meterScaleData[endpoint][scale_index].scale )
		{
			gAppMeterValue_t* pMeterScaleValue = NULL;

			switch( rateType )
			{
				case cc_meter_rateType_Import_Consumed:
				{
					if( cc_meter_rateType_BothSupported == meters[endpoint].rateTypeSupported || cc_meter_rateType_Import_Consumed == meters[endpoint].rateTypeSupported )
					{
						pMeterScaleValue = &meterScaleData[endpoint][scale_index].consumedIn;
					}
				}break;
				case cc_meter_rateType_Export_Produced:
				{
					if( cc_meter_rateType_BothSupported == meters[endpoint].rateTypeSupported || cc_meter_rateType_Import_Consumed == meters[endpoint].rateTypeSupported )
					{
						pMeterScaleValue = &meterScaleData[endpoint][scale_index].producedOut;
					}
				}break;
				default:
					break;
			}

			/* Make sure there isn't a problem with the logic/configuration of the rates. */
			if( NULL == pMeterScaleValue ){
				DPRINTF("... ERROR requested-rate: %02X but supported-rate:%02X", rateType, meters[endpoint].rateTypeSupported);
				return 0;
			}
			DPRINTF(" pre.: %d value:%X last-report time:%d", pMeterScaleValue->precision, pMeterScaleValue->value_actual, pMeterScaleValue->value_reportedConfirmedReceived );
			/* We found the values, so write them to the pointers*/
			*p_precision = pMeterScaleValue->precision;
			*p_currentValue = pMeterScaleValue->value_actual;
			*p_lastValue = pMeterScaleValue->value_reportedConfirmedReceived;

			/* Save the last value reported */
			pMeterScaleValue->value_reported = pMeterScaleValue->value_actual;

			/* Calculate ticks since the last report in seconds */
			uint32_t deltaSeconds =
				cc_meter_time_delta_in_ticks(
						osKernelGetSysTimerCount(),
						pMeterScaleValue->timestampOfLastReport
				);

			DPRINTF(" delta-ms: %d", deltaSeconds);

			/* convert to ticks to seconds */
			deltaSeconds = deltaSeconds / 1000;
			DPRINTF(" delta-sec: %d", deltaSeconds);

			/* Seconds is only 16-bit */
			*p_deltaTimeSeconds = ( deltaSeconds >= UINT16_MAX ) ? UINT16_MAX : (uint16_t)deltaSeconds;

			return pMeterScaleValue->size;
		}
	}


    /* Error not found */
    return 0;
}

void cc_meter_set_meter_value( uint8_t endpoint, cc_meter_rateType_t rateType, cc_meter_scale_t scale, uint32_t currentValue)
{
    if( endpoint >= CC_METER_NUM_ENDPOINTS )
      return;


	for(size_t i = 0; i < CC_METER_NUM_METER_SCALES; ++i)
	{
		if( scale == meterScaleData[endpoint][i].scale )
		{
			switch( rateType )
			{
				case cc_meter_rateType_Import_Consumed:
				{
					meterScaleData[endpoint][i].consumedIn.value_actual = currentValue;
				}break;
				case cc_meter_rateType_Export_Produced:
				{
					meterScaleData[endpoint][i].producedOut.value_actual = currentValue;
				}break;
				default:
					return;
			}
			return;
		}
	}

}


/* This meter doesn't support reset */

bool cc_meter_handle_reset_cmd(uint8_t endpoint, cc_meter_rateType_t rateType, cc_meter_scale_t scale, uint8_t precision, uint8_t size, uint32_t value)
{
	(void)endpoint;
	(void)rateType;
	(void)scale;
	(void)precision;
	(void)size;
	(void)value;
	return false;
}

static bool check_tx_report_status(TRANSMISSION_RESULT * pTransmissionResult)
{
    if( TRANSMISSION_RESULT_FINISHED != pTransmissionResult->isFinished )
        return false;

    DPRINT("\r\n[CC_METER APP] Auto Report  ");

    switch(pTransmissionResult->status)
    {
        case TRANSMIT_COMPLETE_OK:
        case TRANSMIT_COMPLETE_VERIFIED:
            DPRINT("success");
            break;
        default:
            DPRINTF("failure Status:%02X", pTransmissionResult->status);
            return false;
    }

    return true;

}

void cc_meter_report_completed(uint8_t endpoint, cc_meter_scale_t scale, cc_meter_rateType_t rateType)
{
    /* Watts report received OK, so save last report value, and the time stamp of the report. */

	uint32_t currentTime = osKernelGetSysTimerCount();

	DPRINTF("\r\n[CC METER APP]%s> scale:%02X, rate:%02X, Time: ", __func__, scale, rateType, currentTime);

	uint32_t meterScaleIndex = cc_meter_app_get_scale_index(endpoint, scale);

	/* If a rate type isn't specified, then we used the default */
	if( cc_meter_rateType_Unspecified == rateType)
	{
		rateType = meters[endpoint].rateTypeDefault;
	}

	switch( rateType )
	{
		case cc_meter_rateType_Import_Consumed:
		{
			DPRINTF(" import reported: %X", meterScaleData[endpoint][meterScaleIndex].consumedIn.value_reported);
			/* Save value reported as value confirmed to be received */
			meterScaleData[endpoint][meterScaleIndex].consumedIn.value_reportedConfirmedReceived = meterScaleData[endpoint][meterScaleIndex].consumedIn.value_reported;

			/* Save the new time stamp of the last successful report */
			meterScaleData[endpoint][meterScaleIndex].consumedIn.timestampOfLastReport = currentTime;


		}break;

		case cc_meter_rateType_Export_Produced:
		{
			DPRINTF(" export reported: %X", meterScaleData[endpoint][meterScaleIndex].consumedIn.value_reported);
			/* Save value reported as value confirmed to be received */
			meterScaleData[endpoint][meterScaleIndex].producedOut.value_reportedConfirmedReceived = meterScaleData[endpoint][meterScaleIndex].producedOut.value_reported;

			/* Save the new time stamp of the last successful report */
			meterScaleData[endpoint][meterScaleIndex].producedOut.timestampOfLastReport = currentTime;
		}break;
		default:
			DPRINTF("\r\n[CC METER APP]%s> ERROR: rate type wrong:", __func__, rateType);
			return;
	}


}


void meter_report_done_WaterGallonsConsumed(TRANSMISSION_RESULT * pTransmissionResult)
{
	if( false == check_tx_report_status( pTransmissionResult ) ){
		DPRINTF("\r\n[CC METER APP]%s> Tx failed.", __func__);
		return;
	}

    /* Volts report received OK, so save last report value, and the time stamp of the report. */
    cc_meter_report_completed(CC_METER_WATER_ENDPOINT, cc_meter_scale_Water_USGallons, cc_meter_rateType_Import_Consumed);
}


void cc_meter_app_auto_report_timer(SSwTimer* pTimer)
{
	(void)pTimer;
	DPRINTF("\r\n[CC_METER APP]%s>Auto Reporting endpoint 0 gallons.", __func__);
	cc_meter_send_meter_report_WaterGallonsConsumed();
}

void cc_meter_app_set_current_WaterGallonsConsumed(uint32_t total)
{
    meterScaleData[CC_METER_WATER_ENDPOINT][CC_METER_APP_SCALE_INDEX_GALLONS].scale = cc_meter_scale_Water_USGallons;
    /* Not sure if precision should be able to change at run time */
    meterScaleData[CC_METER_WATER_ENDPOINT][CC_METER_APP_SCALE_INDEX_GALLONS].consumedIn.value_actual = total;
}

void cc_meter_send_meter_report_WaterGallonsConsumed(void)
{
	bool tx_OK = false;

	/* Enqueue a meter report for Gallons */
	tx_OK = cc_meter_meterReport_tx(
		  NULL,//Null is lifeline
		  ENDPOINT_ROOT,
		  cc_meter_scale_Water_USGallons,
		  cc_meter_rateType_Import_Consumed,
		  meter_report_done_WaterGallonsConsumed
	);

	if( !tx_OK )
	{
		DPRINT("Couldn't send meter report for gallons.");
	}
}

void cc_meter_app_start_auto_reports(uint32_t milliseconds)
{
	if( 0 != milliseconds ){
		TimerStart(&meter_auto_report_timer, milliseconds );
	}
	else
	{
		TimerStop(&meter_auto_report_timer);
	}
}

