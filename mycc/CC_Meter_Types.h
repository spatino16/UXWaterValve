/*
 * CC_Meter_Types.h
 *
 *  Created on: Jun 21, 2024
 *      Author: brandongruber
 */

#ifndef CC_METER_TYPES_H_
#define CC_METER_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif


#define cc_meter_scale_Electric_kWh         0x00
#define cc_meter_scale_Electric_kVAh        0x01
#define cc_meter_scale_Electric_W           0x02
#define cc_meter_scale_Electric_PulseCount  0x03
#define cc_meter_scale_Electric_V           0x04
#define cc_meter_scale_Electric_A           0x05
#define cc_meter_scale_Electric_PowerFactor 0x06
#define cc_meter_scale_Electric_kVar        0x07
#define cc_meter_scale_Electric_kVarh       0x08

#define cc_meter_scale_Gas_CubicMeters      0x00
#define cc_meter_scale_Gas_CubicFeet        0x01
#define cc_meter_scale_Gas_PulseCount       0x03


#define cc_meter_scale_Water_CubicMeters    0x00
#define cc_meter_scale_Water_CubicFeet      0x01
#define cc_meter_scale_Water_USGallons      0x02
#define cc_meter_scale_Water_PulseCount     0x03


#define cc_meter_scale_Heating_kWh          0x00
#define cc_meter_scale_Cooling_kWh          0x00

typedef uint8_t cc_meter_scale_t;
typedef uint32_t cc_meter_scale_bitMask_t;

typedef enum{
    cc_meter_MeterType_default = 0,
    cc_meter_MeterType_Electric,
    cc_meter_MeterType_Gas,
    cc_meter_MeterType_Water,
    cc_meter_MeterType_Heating,
    cc_meter_MeterType_Cooling,
}cc_meter_meterType_t;

typedef enum{
    cc_meter_rateType_Unspecified = 0,
    cc_meter_rateType_Import_Consumed,
    cc_meter_rateType_Export_Produced,
    cc_meter_rateType_BothSupported,
}cc_meter_rateType_t;

typedef struct {
    cc_meter_meterType_t meterType;
    cc_meter_scale_bitMask_t scalesSupportedBitMask;
    /*these defaults are what are reported on a METER_GET if there is more than one scale or rate type supported, and the METER_GET doesn't specify which scale and/or rate type it is in the get requesting.*/
    cc_meter_scale_t default_scale;
    cc_meter_rateType_t rateTypeDefault:8;
	cc_meter_rateType_t rateTypeSupported:8;
    bool resettable;
}cc_meter_meterInfo_t;





#ifdef __cplusplus
}
#endif


#endif /* CC_METER_TYPES_H_ */
