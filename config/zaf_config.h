/***************************************************************************//**
 * # License
 * <b> Copyright 2023 Silicon Laboratories Inc. www.silabs.com </b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * https://www.silabs.com/about-us/legal/master-software-license-agreement
 * By installing, copying or otherwise using this software, you agree to the
 * terms of the MSLA.
 *
 ******************************************************************************/

#ifndef _ZAF_CONFIG_H_
#define _ZAF_CONFIG_H_

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Command Class Firmware Update - Bootloader update

// <o ZAF_CONFIG_BOOTLOADER_TARGET_ID> The bootloader target id <1..255:1> <f.d>
// <i> If the bootloader update is enabled
// <i> This determines which target id should be used by the bootloader firmware
// <i> Default: 1
#define ZAF_CONFIG_BOOTLOADER_TARGET_ID  1

// <q ZAF_CONFIG_BOOTLOADER_UPGRADABLE> Indicates if the bootloader can be updated
// <i> Includes the bootloader as a target
// <i> Default: 1
#define ZAF_CONFIG_BOOTLOADER_UPGRADABLE  1

// </h>
// <h> Command Class Firmware Update - Firmware targets

// <o ZAF_CONFIG_FIRMWARE_TARGET_COUNT> Number of firmware targets <0..10:1> <f.d>
// <i> Defines the number of supported firmware targets. Setting this number to more than 1 requires
// <i> the application to implement CC_Version_GetFirmwareVersion_handler(). The default value is 1
// <i> because firmware target 0 is the Z-Wave application firmware (including Z-Wave stack).
// <i> Default: 1
#define ZAF_CONFIG_FIRMWARE_TARGET_COUNT  1

// </h>
// <h> Command Class ZwavePlusInfo Configuration

// <o ZAF_CONFIG_USER_ICON_TYPE> User Icon Type
// <i> User Icon Type reported in Z-Wave Plus Info Report Command
// <ICON_TYPE_GENERIC_BARRIER=> GENERIC_BARRIER
// <ICON_TYPE_GENERIC_CENTRAL_CONTROLLER=> GENERIC_CENTRAL_CONTROLLER
// <ICON_TYPE_GENERIC_DIMMER_WALL_SWITCH=> GENERIC_DIMMER_WALL_SWITCH
// <ICON_TYPE_GENERIC_DISPLAY_SIMPLE=> GENERIC_DISPLAY_SIMPLE
// <ICON_TYPE_GENERIC_DOOR_LOCK_KEYPAD=> GENERIC_DOOR_LOCK_KEYPAD
// <ICON_TYPE_GENERIC_ENTRY_CONTROL=> GENERIC_ENTRY_CONTROL
// <ICON_TYPE_GENERIC_FAN_SWITCH=> GENERIC_FAN_SWITCH
// <ICON_TYPE_GENERIC_GATEWAY=> GENERIC_GATEWAY
// <ICON_TYPE_GENERIC_IRRIGATION=> GENERIC_IRRIGATION
// <ICON_TYPE_GENERIC_LIGHT_DIMMER_SWITCH=> GENERIC_LIGHT_DIMMER_SWITCH
// <ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH=> GENERIC_ON_OFF_POWER_SWITCH
// <ICON_TYPE_GENERIC_ON_OFF_WALL_SWITCH=> GENERIC_ON_OFF_WALL_SWITCH
// <ICON_TYPE_GENERIC_POWER_STRIP=> GENERIC_POWER_STRIP
// <ICON_TYPE_GENERIC_REMOTE_CONTROL_AV=> GENERIC_REMOTE_CONTROL_AV
// <ICON_TYPE_GENERIC_REMOTE_CONTROL_MULTI_PURPOSE=> GENERIC_REMOTE_CONTROL_MULTI_PURPOSE
// <ICON_TYPE_GENERIC_REMOTE_CONTROL_SIMPLE=> GENERIC_REMOTE_CONTROL_SIMPLE
// <ICON_TYPE_GENERIC_REPEATER=> GENERIC_REPEATER
// <ICON_TYPE_GENERIC_SENSOR_MULTILEVEL=> GENERIC_SENSOR_MULTILEVEL
// <ICON_TYPE_GENERIC_SENSOR_NOTIFICATION=> GENERIC_SENSOR_NOTIFICATION
// <ICON_TYPE_GENERIC_SET_TOP_BOX=> GENERIC_SET_TOP_BOX
// <ICON_TYPE_GENERIC_SIREN=> GENERIC_SIREN
// <ICON_TYPE_GENERIC_SUB_ENERGY_METER=> GENERIC_SUB_ENERGY_METER
// <ICON_TYPE_GENERIC_SUB_SYSTEM_CONTROLLER=> GENERIC_SUB_SYSTEM_CONTROLLER
// <ICON_TYPE_GENERIC_THERMOSTAT=> GENERIC_THERMOSTAT
// <ICON_TYPE_GENERIC_THERMOSTAT_SETBACK_OBSOLETED=> GENERIC_THERMOSTAT_SETBACK_OBSOLETED
// <ICON_TYPE_GENERIC_TV=> GENERIC_TV
// <ICON_TYPE_GENERIC_VALVE_OPEN_CLOSE=> GENERIC_VALVE_OPEN_CLOSE
// <ICON_TYPE_GENERIC_WALL_CONTROLLER=> GENERIC_WALL_CONTROLLER
// <ICON_TYPE_GENERIC_WHOLE_HOME_METER_SIMPLE=> GENERIC_WHOLE_HOME_METER_SIMPLE
// <ICON_TYPE_GENERIC_WINDOW_COVERING_ENDPOINT_AWARE=> GENERIC_WINDOW_COVERING_ENDPOINT_AWARE
// <ICON_TYPE_GENERIC_WINDOW_COVERING_NO_POSITION_ENDPOINT=> GENERIC_WINDOW_COVERING_NO_POSITION_ENDPOINT
// <ICON_TYPE_GENERIC_WINDOW_COVERING_POSITION_ENDPOINT_AWARE=> GENERIC_WINDOW_COVERING_POSITION_ENDPOINT_AWARE
// <ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_FOUR_BUTTONS=> SPECIFIC_DIMMER_WALL_SWITCH_FOUR_BUTTONS
// <ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_ONE_BUTTON=> SPECIFIC_DIMMER_WALL_SWITCH_ONE_BUTTON
// <ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_ONE_ROTARY=> SPECIFIC_DIMMER_WALL_SWITCH_ONE_ROTARY
// <ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_THREE_BUTTONS=> SPECIFIC_DIMMER_WALL_SWITCH_THREE_BUTTONS
// <ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_TWO_BUTTONS=> SPECIFIC_DIMMER_WALL_SWITCH_TWO_BUTTONS
// <ICON_TYPE_SPECIFIC_ENTRY_CONTROL_KEYPAD_0_9=> SPECIFIC_ENTRY_CONTROL_KEYPAD_0_9
// <ICON_TYPE_SPECIFIC_ENTRY_CONTROL_RFID_TAG_READER_NO_BUTTON=> SPECIFIC_ENTRY_CONTROL_RFID_TAG_READER_NO_BUTTON
// <ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_CEILING_OUTLET=> SPECIFIC_LIGHT_DIMMER_SWITCH_CEILING_OUTLET
// <ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_LAMP_POST_HIGH=> SPECIFIC_LIGHT_DIMMER_SWITCH_LAMP_POST_HIGH
// <ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_LAMP_POST_LOW=> SPECIFIC_LIGHT_DIMMER_SWITCH_LAMP_POST_LOW
// <ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_PLUGIN=> SPECIFIC_LIGHT_DIMMER_SWITCH_PLUGIN
// <ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_WALL_LAMP=> SPECIFIC_LIGHT_DIMMER_SWITCH_WALL_LAMP
// <ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_WALL_OUTLET=> SPECIFIC_LIGHT_DIMMER_SWITCH_WALL_OUTLET
// <ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_CEILING_OUTLET=> SPECIFIC_ON_OFF_POWER_SWITCH_CEILING_OUTLET
// <ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_LAMP_POST_HIGH=> SPECIFIC_ON_OFF_POWER_SWITCH_LAMP_POST_HIGH
// <ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_LAMP_POST_LOW=> SPECIFIC_ON_OFF_POWER_SWITCH_LAMP_POST_LOW
// <ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_PLUGIN=> SPECIFIC_ON_OFF_POWER_SWITCH_PLUGIN
// <ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_WALL_LAMP=> SPECIFIC_ON_OFF_POWER_SWITCH_WALL_LAMP
// <ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_WALL_OUTLET=> SPECIFIC_ON_OFF_POWER_SWITCH_WALL_OUTLET
// <ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_DOOR_BELL=> SPECIFIC_ON_OFF_WALL_SWITCH_DOOR_BELL
// <ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_FOUR_BUTTONS=> SPECIFIC_ON_OFF_WALL_SWITCH_FOUR_BUTTONS
// <ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_ONE_BUTTON=> SPECIFIC_ON_OFF_WALL_SWITCH_ONE_BUTTON
// <ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_ONE_ROTARY=> SPECIFIC_ON_OFF_WALL_SWITCH_ONE_ROTARY
// <ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_THREE_BUTTONS=> SPECIFIC_ON_OFF_WALL_SWITCH_THREE_BUTTONS
// <ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_TWO_BUTTONS=> SPECIFIC_ON_OFF_WALL_SWITCH_TWO_BUTTONS
// <ICON_TYPE_SPECIFIC_POWER_STRIP_INDIVIDUAL_OUTLET=> SPECIFIC_POWER_STRIP_INDIVIDUAL_OUTLET
// <ICON_TYPE_SPECIFIC_REMOTE_CONTROL_SIMPLE_KEYFOB=> SPECIFIC_REMOTE_CONTROL_SIMPLE_KEYFOB
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_AIR_FLOW=> SPECIFIC_SENSOR_MULTILEVEL_AIR_FLOW
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_AIR_TEMPERATURE=> SPECIFIC_SENSOR_MULTILEVEL_AIR_TEMPERATURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ANGLE_POSITION=> SPECIFIC_SENSOR_MULTILEVEL_ANGLE_POSITION
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ATMOSPHERIC_PRESSURE=> SPECIFIC_SENSOR_MULTILEVEL_ATMOSPHERIC_PRESSURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_BAROMETRIC_PRESSURE=> SPECIFIC_SENSOR_MULTILEVEL_BAROMETRIC_PRESSURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_CO2_LEVEL=> SPECIFIC_SENSOR_MULTILEVEL_CO2_LEVEL
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_CURRENT=> SPECIFIC_SENSOR_MULTILEVEL_CURRENT
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DEW_POINT=> SPECIFIC_SENSOR_MULTILEVEL_DEW_POINT
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DIRECTION=> SPECIFIC_SENSOR_MULTILEVEL_DIRECTION
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DISTANCE=> SPECIFIC_SENSOR_MULTILEVEL_DISTANCE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_CONDUCTIVITY=> SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_CONDUCTIVITY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_RESISTIVITY=> SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_RESISTIVITY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_FREQUENCY=> SPECIFIC_SENSOR_MULTILEVEL_FREQUENCY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_GENERAL_PURPOSE_VALUE=> SPECIFIC_SENSOR_MULTILEVEL_GENERAL_PURPOSE_VALUE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_HUMIDITY=> SPECIFIC_SENSOR_MULTILEVEL_HUMIDITY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_LOUDNESS=> SPECIFIC_SENSOR_MULTILEVEL_LOUDNESS
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_LUMINANCE=> SPECIFIC_SENSOR_MULTILEVEL_LUMINANCE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_MOISTURE=> SPECIFIC_SENSOR_MULTILEVEL_MOISTURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_MULTIDEVICE=> SPECIFIC_SENSOR_MULTILEVEL_MULTIDEVICE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_POWER=> SPECIFIC_SENSOR_MULTILEVEL_POWER
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_RAIN_RATE=> SPECIFIC_SENSOR_MULTILEVEL_RAIN_RATE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ROTATION=> SPECIFIC_SENSOR_MULTILEVEL_ROTATION
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_INTENSITY=> SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_INTENSITY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_MAGNITUDE=> SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_MAGNITUDE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SOIL_TEMPERATURE=> SPECIFIC_SENSOR_MULTILEVEL_SOIL_TEMPERATURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SOLOR_RADIATION=> SPECIFIC_SENSOR_MULTILEVEL_SOLOR_RADIATION
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TANK_CAPACITY=> SPECIFIC_SENSOR_MULTILEVEL_TANK_CAPACITY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TARGET_TEMPERATURE=> SPECIFIC_SENSOR_MULTILEVEL_TARGET_TEMPERATURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TIDE_LEVEL=> SPECIFIC_SENSOR_MULTILEVEL_TIDE_LEVEL
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TIME=> SPECIFIC_SENSOR_MULTILEVEL_TIME
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ULTRAVIOLET=> SPECIFIC_SENSOR_MULTILEVEL_ULTRAVIOLET
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_VELOCITY=> SPECIFIC_SENSOR_MULTILEVEL_VELOCITY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_VOLTAGE=> SPECIFIC_SENSOR_MULTILEVEL_VOLTAGE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_TEMPERATURE=> SPECIFIC_SENSOR_MULTILEVEL_WATER_TEMPERATURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WEIGHT=> SPECIFIC_SENSOR_MULTILEVEL_WEIGHT
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_ACCESS_CONTROL=> SPECIFIC_SENSOR_NOTIFICATION_ACCESS_CONTROL
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_APPLIANCE=> SPECIFIC_SENSOR_NOTIFICATION_APPLIANCE
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CLOCK=> SPECIFIC_SENSOR_NOTIFICATION_CLOCK
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CO2_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_CO2_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CO_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_CO_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_EMERGENCY_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_EMERGENCY_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_GAS_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_GAS_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HEAT_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_HEAT_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HOME_HEALTH=> SPECIFIC_SENSOR_NOTIFICATION_HOME_HEALTH
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HOME_SECURITY=> SPECIFIC_SENSOR_NOTIFICATION_HOME_SECURITY
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_IRRIGATION=> SPECIFIC_SENSOR_NOTIFICATION_IRRIGATION
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_MULTIDEVICE=> SPECIFIC_SENSOR_NOTIFICATION_MULTIDEVICE
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_POWER_MANAGEMENT=> SPECIFIC_SENSOR_NOTIFICATION_POWER_MANAGEMENT
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SIREN=> SPECIFIC_SENSOR_NOTIFICATION_SIREN
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SMOKE_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_SMOKE_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SYSTEM=> SPECIFIC_SENSOR_NOTIFICATION_SYSTEM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WATER_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_WATER_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WATER_VALVE=> SPECIFIC_SENSOR_NOTIFICATION_WATER_VALVE
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WEATHER_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_WEATHER_ALARM
// <ICON_TYPE_SPECIFIC_THERMOSTAT_LINE_VOLTAGE=> SPECIFIC_THERMOSTAT_LINE_VOLTAGE
// <ICON_TYPE_SPECIFIC_THERMOSTAT_SETBACK=> SPECIFIC_THERMOSTAT_SETBACK
// <i> Default: ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH
#define ZAF_CONFIG_USER_ICON_TYPE  ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH

// <o ZAF_CONFIG_INSTALLER_ICON_TYPE> Installer Icon Type
// <i> Installer Icon Type reported in Z-Wave Plus Info Report Command
// <ICON_TYPE_GENERIC_BARRIER=> GENERIC_BARRIER
// <ICON_TYPE_GENERIC_CENTRAL_CONTROLLER=> GENERIC_CENTRAL_CONTROLLER
// <ICON_TYPE_GENERIC_DIMMER_WALL_SWITCH=> GENERIC_DIMMER_WALL_SWITCH
// <ICON_TYPE_GENERIC_DISPLAY_SIMPLE=> GENERIC_DISPLAY_SIMPLE
// <ICON_TYPE_GENERIC_DOOR_LOCK_KEYPAD=> GENERIC_DOOR_LOCK_KEYPAD
// <ICON_TYPE_GENERIC_ENTRY_CONTROL=> GENERIC_ENTRY_CONTROL
// <ICON_TYPE_GENERIC_FAN_SWITCH=> GENERIC_FAN_SWITCH
// <ICON_TYPE_GENERIC_GATEWAY=> GENERIC_GATEWAY
// <ICON_TYPE_GENERIC_IRRIGATION=> GENERIC_IRRIGATION
// <ICON_TYPE_GENERIC_LIGHT_DIMMER_SWITCH=> GENERIC_LIGHT_DIMMER_SWITCH
// <ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH=> GENERIC_ON_OFF_POWER_SWITCH
// <ICON_TYPE_GENERIC_ON_OFF_WALL_SWITCH=> GENERIC_ON_OFF_WALL_SWITCH
// <ICON_TYPE_GENERIC_POWER_STRIP=> GENERIC_POWER_STRIP
// <ICON_TYPE_GENERIC_REMOTE_CONTROL_AV=> GENERIC_REMOTE_CONTROL_AV
// <ICON_TYPE_GENERIC_REMOTE_CONTROL_MULTI_PURPOSE=> GENERIC_REMOTE_CONTROL_MULTI_PURPOSE
// <ICON_TYPE_GENERIC_REMOTE_CONTROL_SIMPLE=> GENERIC_REMOTE_CONTROL_SIMPLE
// <ICON_TYPE_GENERIC_REPEATER=> GENERIC_REPEATER
// <ICON_TYPE_GENERIC_SENSOR_MULTILEVEL=> GENERIC_SENSOR_MULTILEVEL
// <ICON_TYPE_GENERIC_SENSOR_NOTIFICATION=> GENERIC_SENSOR_NOTIFICATION
// <ICON_TYPE_GENERIC_SET_TOP_BOX=> GENERIC_SET_TOP_BOX
// <ICON_TYPE_GENERIC_SIREN=> GENERIC_SIREN
// <ICON_TYPE_GENERIC_SUB_ENERGY_METER=> GENERIC_SUB_ENERGY_METER
// <ICON_TYPE_GENERIC_SUB_SYSTEM_CONTROLLER=> GENERIC_SUB_SYSTEM_CONTROLLER
// <ICON_TYPE_GENERIC_THERMOSTAT=> GENERIC_THERMOSTAT
// <ICON_TYPE_GENERIC_THERMOSTAT_SETBACK_OBSOLETED=> GENERIC_THERMOSTAT_SETBACK_OBSOLETED
// <ICON_TYPE_GENERIC_TV=> GENERIC_TV
// <ICON_TYPE_GENERIC_VALVE_OPEN_CLOSE=> GENERIC_VALVE_OPEN_CLOSE
// <ICON_TYPE_GENERIC_WALL_CONTROLLER=> GENERIC_WALL_CONTROLLER
// <ICON_TYPE_GENERIC_WHOLE_HOME_METER_SIMPLE=> GENERIC_WHOLE_HOME_METER_SIMPLE
// <ICON_TYPE_GENERIC_WINDOW_COVERING_ENDPOINT_AWARE=> GENERIC_WINDOW_COVERING_ENDPOINT_AWARE
// <ICON_TYPE_GENERIC_WINDOW_COVERING_NO_POSITION_ENDPOINT=> GENERIC_WINDOW_COVERING_NO_POSITION_ENDPOINT
// <ICON_TYPE_GENERIC_WINDOW_COVERING_POSITION_ENDPOINT_AWARE=> GENERIC_WINDOW_COVERING_POSITION_ENDPOINT_AWARE
// <ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_FOUR_BUTTONS=> SPECIFIC_DIMMER_WALL_SWITCH_FOUR_BUTTONS
// <ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_ONE_BUTTON=> SPECIFIC_DIMMER_WALL_SWITCH_ONE_BUTTON
// <ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_ONE_ROTARY=> SPECIFIC_DIMMER_WALL_SWITCH_ONE_ROTARY
// <ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_THREE_BUTTONS=> SPECIFIC_DIMMER_WALL_SWITCH_THREE_BUTTONS
// <ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_TWO_BUTTONS=> SPECIFIC_DIMMER_WALL_SWITCH_TWO_BUTTONS
// <ICON_TYPE_SPECIFIC_ENTRY_CONTROL_KEYPAD_0_9=> SPECIFIC_ENTRY_CONTROL_KEYPAD_0_9
// <ICON_TYPE_SPECIFIC_ENTRY_CONTROL_RFID_TAG_READER_NO_BUTTON=> SPECIFIC_ENTRY_CONTROL_RFID_TAG_READER_NO_BUTTON
// <ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_CEILING_OUTLET=> SPECIFIC_LIGHT_DIMMER_SWITCH_CEILING_OUTLET
// <ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_LAMP_POST_HIGH=> SPECIFIC_LIGHT_DIMMER_SWITCH_LAMP_POST_HIGH
// <ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_LAMP_POST_LOW=> SPECIFIC_LIGHT_DIMMER_SWITCH_LAMP_POST_LOW
// <ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_PLUGIN=> SPECIFIC_LIGHT_DIMMER_SWITCH_PLUGIN
// <ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_WALL_LAMP=> SPECIFIC_LIGHT_DIMMER_SWITCH_WALL_LAMP
// <ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_WALL_OUTLET=> SPECIFIC_LIGHT_DIMMER_SWITCH_WALL_OUTLET
// <ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_CEILING_OUTLET=> SPECIFIC_ON_OFF_POWER_SWITCH_CEILING_OUTLET
// <ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_LAMP_POST_HIGH=> SPECIFIC_ON_OFF_POWER_SWITCH_LAMP_POST_HIGH
// <ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_LAMP_POST_LOW=> SPECIFIC_ON_OFF_POWER_SWITCH_LAMP_POST_LOW
// <ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_PLUGIN=> SPECIFIC_ON_OFF_POWER_SWITCH_PLUGIN
// <ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_WALL_LAMP=> SPECIFIC_ON_OFF_POWER_SWITCH_WALL_LAMP
// <ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_WALL_OUTLET=> SPECIFIC_ON_OFF_POWER_SWITCH_WALL_OUTLET
// <ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_DOOR_BELL=> SPECIFIC_ON_OFF_WALL_SWITCH_DOOR_BELL
// <ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_FOUR_BUTTONS=> SPECIFIC_ON_OFF_WALL_SWITCH_FOUR_BUTTONS
// <ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_ONE_BUTTON=> SPECIFIC_ON_OFF_WALL_SWITCH_ONE_BUTTON
// <ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_ONE_ROTARY=> SPECIFIC_ON_OFF_WALL_SWITCH_ONE_ROTARY
// <ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_THREE_BUTTONS=> SPECIFIC_ON_OFF_WALL_SWITCH_THREE_BUTTONS
// <ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_TWO_BUTTONS=> SPECIFIC_ON_OFF_WALL_SWITCH_TWO_BUTTONS
// <ICON_TYPE_SPECIFIC_POWER_STRIP_INDIVIDUAL_OUTLET=> SPECIFIC_POWER_STRIP_INDIVIDUAL_OUTLET
// <ICON_TYPE_SPECIFIC_REMOTE_CONTROL_SIMPLE_KEYFOB=> SPECIFIC_REMOTE_CONTROL_SIMPLE_KEYFOB
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_AIR_FLOW=> SPECIFIC_SENSOR_MULTILEVEL_AIR_FLOW
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_AIR_TEMPERATURE=> SPECIFIC_SENSOR_MULTILEVEL_AIR_TEMPERATURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ANGLE_POSITION=> SPECIFIC_SENSOR_MULTILEVEL_ANGLE_POSITION
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ATMOSPHERIC_PRESSURE=> SPECIFIC_SENSOR_MULTILEVEL_ATMOSPHERIC_PRESSURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_BAROMETRIC_PRESSURE=> SPECIFIC_SENSOR_MULTILEVEL_BAROMETRIC_PRESSURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_CO2_LEVEL=> SPECIFIC_SENSOR_MULTILEVEL_CO2_LEVEL
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_CURRENT=> SPECIFIC_SENSOR_MULTILEVEL_CURRENT
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DEW_POINT=> SPECIFIC_SENSOR_MULTILEVEL_DEW_POINT
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DIRECTION=> SPECIFIC_SENSOR_MULTILEVEL_DIRECTION
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DISTANCE=> SPECIFIC_SENSOR_MULTILEVEL_DISTANCE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_CONDUCTIVITY=> SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_CONDUCTIVITY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_RESISTIVITY=> SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_RESISTIVITY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_FREQUENCY=> SPECIFIC_SENSOR_MULTILEVEL_FREQUENCY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_GENERAL_PURPOSE_VALUE=> SPECIFIC_SENSOR_MULTILEVEL_GENERAL_PURPOSE_VALUE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_HUMIDITY=> SPECIFIC_SENSOR_MULTILEVEL_HUMIDITY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_LOUDNESS=> SPECIFIC_SENSOR_MULTILEVEL_LOUDNESS
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_LUMINANCE=> SPECIFIC_SENSOR_MULTILEVEL_LUMINANCE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_MOISTURE=> SPECIFIC_SENSOR_MULTILEVEL_MOISTURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_MULTIDEVICE=> SPECIFIC_SENSOR_MULTILEVEL_MULTIDEVICE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_POWER=> SPECIFIC_SENSOR_MULTILEVEL_POWER
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_RAIN_RATE=> SPECIFIC_SENSOR_MULTILEVEL_RAIN_RATE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ROTATION=> SPECIFIC_SENSOR_MULTILEVEL_ROTATION
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_INTENSITY=> SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_INTENSITY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_MAGNITUDE=> SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_MAGNITUDE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SOIL_TEMPERATURE=> SPECIFIC_SENSOR_MULTILEVEL_SOIL_TEMPERATURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SOLOR_RADIATION=> SPECIFIC_SENSOR_MULTILEVEL_SOLOR_RADIATION
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TANK_CAPACITY=> SPECIFIC_SENSOR_MULTILEVEL_TANK_CAPACITY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TARGET_TEMPERATURE=> SPECIFIC_SENSOR_MULTILEVEL_TARGET_TEMPERATURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TIDE_LEVEL=> SPECIFIC_SENSOR_MULTILEVEL_TIDE_LEVEL
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TIME=> SPECIFIC_SENSOR_MULTILEVEL_TIME
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ULTRAVIOLET=> SPECIFIC_SENSOR_MULTILEVEL_ULTRAVIOLET
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_VELOCITY=> SPECIFIC_SENSOR_MULTILEVEL_VELOCITY
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_VOLTAGE=> SPECIFIC_SENSOR_MULTILEVEL_VOLTAGE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_TEMPERATURE=> SPECIFIC_SENSOR_MULTILEVEL_WATER_TEMPERATURE
// <ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WEIGHT=> SPECIFIC_SENSOR_MULTILEVEL_WEIGHT
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_ACCESS_CONTROL=> SPECIFIC_SENSOR_NOTIFICATION_ACCESS_CONTROL
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_APPLIANCE=> SPECIFIC_SENSOR_NOTIFICATION_APPLIANCE
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CLOCK=> SPECIFIC_SENSOR_NOTIFICATION_CLOCK
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CO2_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_CO2_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CO_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_CO_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_EMERGENCY_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_EMERGENCY_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_GAS_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_GAS_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HEAT_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_HEAT_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HOME_HEALTH=> SPECIFIC_SENSOR_NOTIFICATION_HOME_HEALTH
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HOME_SECURITY=> SPECIFIC_SENSOR_NOTIFICATION_HOME_SECURITY
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_IRRIGATION=> SPECIFIC_SENSOR_NOTIFICATION_IRRIGATION
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_MULTIDEVICE=> SPECIFIC_SENSOR_NOTIFICATION_MULTIDEVICE
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_POWER_MANAGEMENT=> SPECIFIC_SENSOR_NOTIFICATION_POWER_MANAGEMENT
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SIREN=> SPECIFIC_SENSOR_NOTIFICATION_SIREN
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SMOKE_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_SMOKE_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SYSTEM=> SPECIFIC_SENSOR_NOTIFICATION_SYSTEM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WATER_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_WATER_ALARM
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WATER_VALVE=> SPECIFIC_SENSOR_NOTIFICATION_WATER_VALVE
// <ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WEATHER_ALARM=> SPECIFIC_SENSOR_NOTIFICATION_WEATHER_ALARM
// <ICON_TYPE_SPECIFIC_THERMOSTAT_LINE_VOLTAGE=> SPECIFIC_THERMOSTAT_LINE_VOLTAGE
// <ICON_TYPE_SPECIFIC_THERMOSTAT_SETBACK=> SPECIFIC_THERMOSTAT_SETBACK
// <i> Default: ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH
#define ZAF_CONFIG_INSTALLER_ICON_TYPE  ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH

// </h>
// <h> Version Configuration

// <o ZAF_CONFIG_HARDWARE_VERSION> Hardware version <0..255:1> <f.d>
// <i> The Hardware Version field MUST report a value which is unique to this particular
// <i> version of the product. It MUST be possible to uniquely determine the hardware
// <i> characteristics from the Hardware Version field in combination with the Manufacturer
// <i> ID, Product Type ID and Product ID fields of Manufacturer Specific Info Report
// <i> of the Manufacturer Specific Command Class.
// <i> This information allows a user to pick a firmware image version that is guaranteed
// <i> to work with this particular version of the product.
// <i> Note that the Hardware Version field is intended for the hardware version of the
// <i> entire product, not just the version of the Z-Wave radio chip.
// <i> Default: 1
#define ZAF_CONFIG_HARDWARE_VERSION  1

// </h>
// <h> Command Class Manufacturer Specific

// <o ZAF_CONFIG_MANUFACTURER_ID> Manufacturer ID <0x0000..0xFFFF:0x1> <f.h>
// <i> The default value is set to 0x0000 which is Silicon Labs.
// <i> The value must be updated according to the official list of manufacturers in the Z-Wave Alliance.
// <i> Default: 0x0000
#define ZAF_CONFIG_MANUFACTURER_ID  0x0000

// <o ZAF_CONFIG_PRODUCT_TYPE_ID> Product Type ID <0x0000..0xFFFF:0x1> <f.h>
// <i> Default is 4 which is a value chosen by Silabs.
// <i> Silabs consider this to indicate that the device is a Z-Wave Plus Version 2 device.
// <i> Default: 0x0004
#define ZAF_CONFIG_PRODUCT_TYPE_ID  0x0004

// <o ZAF_CONFIG_PRODUCT_ID> Product ID <0x0000..0xFFFF:0x1> <f.h>
// <i> Default is 0 which is invalid in the context of Silicon Labs Z-Wave apps. According to CC
// <i> Manufacturer Specific specification, zero is a valid value and can be used as a product ID.
// <i> Default: 0x0000
#define ZAF_CONFIG_PRODUCT_ID  2

// </h>
// <h> Device type

// <o ZAF_CONFIG_GENERIC_TYPE> The generic type of a device.
// <i> The generic type of a device. A certain device type requires a generic type, e.g., the Lock device type requires the generic type to be Entry Control.
// <i> Find more info in the Z-Wave Plus v2 Device Type specification.
// <GENERIC_TYPE_AV_CONTROL_POINT=> AV Control Point
// <GENERIC_TYPE_ENTRY_CONTROL=> Entry Control
// <GENERIC_TYPE_GENERIC_CONTROLLER=> Generic Controller
// <GENERIC_TYPE_METER=> Meter
// <GENERIC_TYPE_REPEATER_SLAVE=> Repeater End Device
// <GENERIC_TYPE_SENSOR_MULTILEVEL=> Sensor Multilevel
// <GENERIC_TYPE_SWITCH_BINARY=> Switch Binary
// <GENERIC_TYPE_SWITCH_MULTILEVEL=> Switch Multilevel
// <GENERIC_TYPE_THERMOSTAT=> Thermostat
// <GENERIC_TYPE_WALL_CONTROLLER=> Wall Controller
// <GENERIC_TYPE_SENSOR_NOTIFICATION=> Sensor Notification
// <i> Default: 0
#define ZAF_CONFIG_GENERIC_TYPE  GENERIC_TYPE_SWITCH_BINARY

// <o ZAF_CONFIG_SPECIFIC_TYPE> The specific type of a device.
// <i> The specific type of a device. A certain device type requires a specific type, e.g., the Lock device type requires the specific type to be Door Lock.
// <i> Find more info in the Z-Wave Plus v2 Device Type specification.
// <SPECIFIC_TYPE_NOT_USED=> Specific type not used
// <SPECIFIC_TYPE_DOOR_LOCK=> Door Lock
// <SPECIFIC_TYPE_SECURE_GATE=> Secure Gate
// <SPECIFIC_TYPE_SECURE_BARRIER_OPEN_ONLY=> Secure Barrier (open only)
// <SPECIFIC_TYPE_SECURE_BARRIER_CLOSE_ONLY=> Secure Barrier (close only)
// <SPECIFIC_TYPE_COLOR_TUNABLE_BINARY=> Color Tunable Binary
// <SPECIFIC_TYPE_COLOR_TUNABLE_MULTILEVEL=> Color Tunable Multilevel
// <SPECIFIC_TYPE_CLASS_A_MOTOR_CONTROL=> Class A Motor Control
// <SPECIFIC_TYPE_CLASS_B_MOTOR_CONTROL=> Class B Motor Control
// <SPECIFIC_TYPE_CLASS_C_MOTOR_CONTROL=> Class C Motor Control
// <SPECIFIC_TYPE_THERMOSTAT_GENERAL_V2=> Thermostat General Version 2
// <SPECIFIC_TYPE_SOUND_SWITCH=> Sound Switch
// <SPECIFIC_TYPE_SECURE_KEYPAD=> Secure Keypad
// <SPECIFIC_TYPE_ROUTING_SENSOR_MULTILEVEL=> Routing Sensor Multilevel
// <SPECIFIC_TYPE_NOTIFICATION_SENSOR=> Notification Sensor
// <SPECIFIC_TYPE_REPEATER_SLAVE=> Repeater End Device
// <SPECIFIC_TYPE_IR_REPEATER=> Infrared Repeater
// <i> Default: SPECIFIC_TYPE_NOT_USED
#define ZAF_CONFIG_SPECIFIC_TYPE  SPECIFIC_TYPE_NOT_USED

// </h>
// <h> Multi Channel Configuration

// <o ZAF_CONFIG_NUMBER_OF_END_POINTS> Number of end points <0..255:1> <f.d>
// <i> Default: 0
#define ZAF_CONFIG_NUMBER_OF_END_POINTS  0

// </h>
// <h> Security Configuration

// <q ZAF_CONFIG_REQUEST_KEY_S0> Request S0 network key
// <i> Default: 0
#define ZAF_CONFIG_REQUEST_KEY_S0  1

// <q ZAF_CONFIG_REQUEST_KEY_S2_UNAUTHENTICATED> Request S2 Unauthenticated network key
// <i> Default: 0
#define ZAF_CONFIG_REQUEST_KEY_S2_UNAUTHENTICATED  1

// <q ZAF_CONFIG_REQUEST_KEY_S2_AUTHENTICATED> Request S2 Authenticated network key
// <i> Default: 0
#define ZAF_CONFIG_REQUEST_KEY_S2_AUTHENTICATED  1

// <q ZAF_CONFIG_REQUEST_KEY_S2_ACCESS> Request S2 Access network key
// <i> Default: 0
#define ZAF_CONFIG_REQUEST_KEY_S2_ACCESS  0

// <q ZAF_CONFIG_SECURE_ONLY> Application can only be controlled when included securely
// <i> Default: 0
#define ZAF_CONFIG_SECURE_ONLY  0

// </h>

// <<< end of configuration section >>>

#endif /* _ZAF_CONFIG_H_ */
