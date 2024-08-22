/*
 * CC_Clock.h
 *
 *  Created on: Aug 2024
 *      Author: Sebas
 */

#ifndef CC_CLOCK_H_
#define CC_CLOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <ZAF_types.h>

// Define Clock Command Class commands
#define COMMAND_CLASS_CLOCK                       0x81
#define CLOCK_VERSION_V1                          0x01
#define CLOCK_SET                                 0x04
#define CLOCK_GET                                 0x05
#define CLOCK_REPORT                              0x06

// Define Clock Weekday values
#define CLOCK_WEEKDAY_UNKNOWN   0x00
#define CLOCK_WEEKDAY_MONDAY    0x01
#define CLOCK_WEEKDAY_TUESDAY   0x02
#define CLOCK_WEEKDAY_WEDNESDAY 0x03
#define CLOCK_WEEKDAY_THURSDAY  0x04
#define CLOCK_WEEKDAY_FRIDAY    0x05
#define CLOCK_WEEKDAY_SATURDAY  0x06
#define CLOCK_WEEKDAY_SUNDAY    0x07

#ifdef __cplusplus
}
#endif

#endif /* CC_CLOCK_H_ */
