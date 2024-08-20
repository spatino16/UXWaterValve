#ifndef __CC_METER_APP_H__
#define __CC_METER_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#define CC_METER_NUM_ENDPOINTS 1
#define CC_METER_NUM_METER_SCALES 1

#define CC_METER_APP_GALLONS_PRECISION 1
#define CC_METER_APP_GALLONS_SIZE 4

#define CC_METER_TIMER_AUTOREPORT_TIME_MS (30ul*1000ul)


#define CC_METER_APP_SCALE_INDEX_GALLONS 0
#define CC_METER_WATER_ENDPOINT 0

void cc_meter_app_set_current_WaterGallonsConsumed(uint32_t total);
void cc_meter_send_meter_report_WaterGallonsConsumed(void);

void cc_meter_app_start_auto_reports(uint32_t milliseconds);
#define cc_meter_app_stop_auto_reports() cc_meter_app_start_auto_reports(0)

#ifdef __cplusplus
}
#endif


#endif
