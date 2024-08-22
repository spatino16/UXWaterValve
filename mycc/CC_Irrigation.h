/*
 * CC_Irrigation.h
 *
 *  Created on: Aug 2024
 *      Author: Sebas
 */

#ifndef CC_IRRIGATION_H_
#define CC_IRRIGATION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <ZAF_types.h>

// Define Irrigation Command Class commands
#define COMMAND_CLASS_IRRIGATION                   0x6B
#define IRRIGATION_VERSION_V1                      0x01
#define IRRIGATION_SYSTEM_INFO_GET                 0x01
#define IRRIGATION_SYSTEM_INFO_REPORT              0x02
#define IRRIGATION_SYSTEM_STATUS_GET               0x03
#define IRRIGATION_SYSTEM_STATUS_REPORT            0x04

// Add other necessary Irrigation commands here..., like SET or CONFIG...

void cc_irrigation_init_cb(void);
void cc_irrigation_app_factory_reset(void);

#ifdef __cplusplus
}
#endif

#endif /* CC_IRRIGATION_H_ */
