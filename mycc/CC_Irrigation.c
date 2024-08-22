/**
 * @file
 * Handler for Command Class Irrigation.
 * @copyright 2024 Your Company
 * @author Your Name
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
#include "CC_Irrigation.h"

#define DEBUGPRINT
#include "DebugPrint.h"

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/
static received_frame_status_t
CC_Irrigation_handler(
    cc_handler_input_t * pInput,
    cc_handler_output_t * pOutput
);

size_t cc_irrigation_construct_systemInfoReport(uint8_t* p_frame);
size_t cc_irrigation_construct_systemStatusReport(uint8_t* p_frame);

size_t cc_irrigation_construct_systemInfoReport(uint8_t* p_frame) {

    // Try 7 // implementation
    size_t frame_index = 0;
    p_frame[frame_index++] = COMMAND_CLASS_IRRIGATION;
    p_frame[frame_index++] = IRRIGATION_SYSTEM_INFO_REPORT;

    // Fill in fields according to doc, set numbers manually in the meantime
    p_frame[frame_index++] = 0; // Reserved and Main Valve fields
    p_frame[frame_index++] = 5; // Total Number of Valves
    p_frame[frame_index++] = 3; // Total Number of Valve Tables
    p_frame[frame_index++] = 10; // Valve Table Max Size
    p_frame[frame_index++] = 0; // Reserved fields

    return frame_index;
}

size_t cc_irrigation_construct_systemStatusReport(uint8_t* p_frame) {

    // Try 4 implementation
    size_t frame_index = 0;
    p_frame[frame_index++] = COMMAND_CLASS_IRRIGATION;
    p_frame[frame_index++] = IRRIGATION_SYSTEM_STATUS_REPORT;

    // Fill in fields according to doc, set numbers manually in the meantime
    p_frame[frame_index++] = 0; // System Voltage
    p_frame[frame_index++] = 0; // Sensor Status
    p_frame[frame_index++] = 2; // Flow Precision
    p_frame[frame_index++] = 4; // Flow Scale
    p_frame[frame_index++] = 0; // Flow Size
    // Additional fields for flow value, pressure, etc.

    return frame_index;
}

static received_frame_status_t
CC_Irrigation_handler(
    cc_handler_input_t * pInput,
    cc_handler_output_t * pOutput
) {
    bool responseExpected = false;

    DPRINT("\r\n[CC IRRIGATION]");

    switch (pInput->frame->ZW_Common.cmd) {
        case IRRIGATION_SYSTEM_INFO_GET:
            if (true == Check_not_legal_response_job(pInput->rx_options)) {
                return RECEIVED_FRAME_STATUS_FAIL;
            }
            DPRINT(" response expected...");
            responseExpected = true;

            pOutput->length = cc_irrigation_construct_systemInfoReport((uint8_t*)&pOutput->frame->ZW_Common.cmdClass);
            break;

        case IRRIGATION_SYSTEM_STATUS_GET:
            if (true == Check_not_legal_response_job(pInput->rx_options)) {
                return RECEIVED_FRAME_STATUS_FAIL;
            }
            DPRINT(" response expected...");
            responseExpected = true;

            pOutput->length = cc_irrigation_construct_systemStatusReport((uint8_t*)&pOutput->frame->ZW_Common.cmdClass);
            break;

        // more stuff or commands

        default:
            return RECEIVED_FRAME_STATUS_NO_SUPPORT;
    }

    if (responseExpected && pOutput->length < 1) {
        return RECEIVED_FRAME_STATUS_FAIL;
    }

    return RECEIVED_FRAME_STATUS_SUCCESS;
}

static uint8_t cc_irrigation_lifeline_report_get(cc_group_t * p_cc_pair) {
    p_cc_pair->cmd = IRRIGATION_SYSTEM_STATUS_REPORT;
    p_cc_pair->cmdClass = COMMAND_CLASS_IRRIGATION;
    return 1;
}

void cc_irrigation_init_cb(void) {
    // Initialize any necessary data structures or values
}

void cc_irrigation_app_factory_reset(void) {
    // Handle any factory reset operations  // To check
}

REGISTER_CC_V5(COMMAND_CLASS_IRRIGATION, IRRIGATION_VERSION_V1, CC_Irrigation_handler, NULL, NULL, cc_irrigation_lifeline_report_get, 0, cc_irrigation_init_cb, cc_irrigation_app_factory_reset);
