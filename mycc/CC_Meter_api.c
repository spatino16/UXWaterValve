/*
 * CC_Meter_api.c
 *
 *  Created on: Jun 20, 2024
 *      Author: brandongruber
 */


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>

#include "CC_Meter_Types.h"

#include "CC_Meter.h"


typedef struct{
    size_t numMeterEndPoints;
    cc_meter_meterInfo_t * p_meterInfo;
}cc_meter_context_t;

static cc_meter_context_t gCCMeterContext = {0};


void cc_meter_init_cb(void)
{
    gCCMeterContext.numMeterEndPoints = cc_meter_app_init(&gCCMeterContext.p_meterInfo);

}
/*
void cc_meter_add_supported_scales(cc_meter_meterInfo_t * p_meterInfo, size_t numScales, cc_meter_scale_t* p_supportedScales) {


    for (size_t i = 0; i < numScales; i++)
    {
        cc_meter_scale_t bitIndex = p_supportedScales[i];

        if (bitIndex < (sizeof(cc_meter_scale_bitMask_t)*8)) {

            p_meterInfo->scalesSupportedBitMask |= (1U << bitIndex);
        }
    }

}*/

/*
 * Look up a meter information struct by it's Z-Wave endpoint.
 *
 * */
bool cc_meter_get_meterInfo(uint8_t endpoint, cc_meter_meterInfo_t** pp_meterData)
{
    if( NULL == pp_meterData || NULL == gCCMeterContext.p_meterInfo || gCCMeterContext.numMeterEndPoints < 1 )
        return false;

    *pp_meterData = NULL;

    if( endpoint < gCCMeterContext.numMeterEndPoints )
    {

		*pp_meterData = &gCCMeterContext.p_meterInfo[endpoint];
		return true;

    }

    return false;
}

__attribute__ ((weak)) void cc_meter_app_factory_reset(void)
{
/* Factory reset not handled */
}

