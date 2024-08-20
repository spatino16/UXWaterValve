/*
 * CC_Meter.h
 *
 *  Created on: Jun 20, 2024
 *      Author: brandongruber
 */

#ifndef CC_METER_H_
#define CC_METER_H_


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "CC_Meter_Types.h"
#include <ZAF_types.h>


bool cc_meter_get_meterInfo(uint8_t endpoint, cc_meter_meterInfo_t** pp_meterData);

//void cc_meter_add_supported_scales(cc_meter_meterInfo_t * p_meterInfo, size_t numScales, cc_meter_scale_t* p_supportedScales);

#define cc_meter_scale_to_bit_mask(SCALEVALUE) (1 << SCALEVALUE)

void cc_meter_init_cb(void);


void cc_meter_app_factory_reset(void);

/* You should use the callback to save a time stamp, so you can calculate the seconds between reports, and using the callback allows you to do this only when transmitting the report was successfully communicated. */
bool
cc_meter_meterReport_tx(
  const agi_profile_t* pProfile,
  uint8_t sourceEndpoint,
  cc_meter_scale_t scale,
  cc_meter_rateType_t rateType,
  VOID_CALLBACKFUNC(pCbFunc)(TRANSMISSION_RESULT * pTransmissionResult));

/* This saves the last value and time that a meter report was successfully comunicated.
 * Should be called by the command class handler on a report and in the callback for when you transmit a meter report successfully manually. */
extern void cc_meter_report_completed(uint8_t endpoint, cc_meter_scale_t scale, cc_meter_rateType_t rateType);


/* cc_meter_handle_get_meter_value is not intended for the application to get the value of the meter only the command class itself. */
extern size_t cc_meter_handle_get_meter_value( uint8_t endpoint, cc_meter_rateType_t rateType, cc_meter_scale_t scale, uint8_t* p_precision, uint32_t* p_currentValue, uint32_t *p_lastValue, uint16_t* p_deltaTimeSeconds);

/* Used by the application to set the value. Does not transmit anything. */
extern void cc_meter_set_meter_value( uint8_t endpoint, cc_meter_rateType_t rateType, cc_meter_scale_t scale, uint32_t currentValue);

extern bool cc_meter_handle_reset_cmd(uint8_t endpoint, cc_meter_rateType_t rateType, cc_meter_scale_t scale, uint8_t precision, uint8_t size, uint32_t value);
extern size_t cc_meter_app_init(cc_meter_meterInfo_t ** pp_meterInfo);

#ifdef __cplusplus
}
#endif



#endif /* CC_METER_H_ */
