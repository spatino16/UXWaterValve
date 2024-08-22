/**
 * @file
 * Handler for Command Class Clock.
 * @copyright 2024 Your Company
 * @author Your Name
 */

#include "ZAF_types.h"
#include "ZW_TransportEndpoint.h"
#include "ZW_TransportSecProtocol.h"
#include "ZAF_Common_interface.h"
#include "zaf_transport_tx.h"
#include "zaf_config_api.h"
#include "zpal_misc.h"
#include <stdbool.h>
#include <stdint.h>
#include "CC_Clock.h"

#define DEBUGPRINT
#include "DebugPrint.h"

static received_frame_status_t CC_Clock_handler(
    cc_handler_input_t * pInput,
    cc_handler_output_t * pOutput
);

static size_t cc_clock_construct_report(uint8_t* p_frame);

static size_t cc_clock_construct_report(uint8_t* p_frame) {
    size_t frame_index = 0;
    p_frame[frame_index++] = COMMAND_CLASS_CLOCK;
    p_frame[frame_index++] = CLOCK_REPORT;

    // Definir los valores correctos para el reporte
    uint8_t weekday = 0x03; // Martes
    uint8_t hour = 0x10;  // 16 (4 PM)
    uint8_t minute = 0x30; // 30 minutos

    // Aplicar máscara para asegurar que weekday es de 3 bits
    weekday &= 0x07;

    // Imprimir valores para depuración
    char debug_string[64];
    snprintf(debug_string, sizeof(debug_string), "Setting values: Weekday=%02X, Hour=%02X, Minute=%02X", weekday, hour, minute);
    DPRINT(debug_string);

    // Asignar los valores en el orden correcto
    p_frame[frame_index++] = weekday; // Primer byte después del comando
    p_frame[frame_index++] = hour;    // Segundo byte
    p_frame[frame_index++] = minute;  // Tercer byte

    return frame_index;
}

static received_frame_status_t CC_Clock_handler(
    cc_handler_input_t * pInput,
    cc_handler_output_t * pOutput
) {
    bool responseExpected = false;

    DPRINT("\r\n[CC CLOCK]");

    switch (pInput->frame->ZW_Common.cmd) {
        case CLOCK_GET:
            if (true == Check_not_legal_response_job(pInput->rx_options)) {
                return RECEIVED_FRAME_STATUS_FAIL;
            }
            DPRINT(" response expected...");
            responseExpected = true;

            // Construir y enviar el reporte
            pOutput->length = cc_clock_construct_report((uint8_t*)&pOutput->frame->ZW_Common.cmdClass);
            break;

        case CLOCK_SET:
            DPRINT("Clock set command received...");
            // Asegurarse de que el índice sea correcto para acceder a los campos
            uint8_t received_weekday = pInput->frame->ZW_Common.cmdClass + 2;
            if (received_weekday > 0x07) {
                // Manejar un valor de weekday no válido
                return RECEIVED_FRAME_STATUS_FAIL;
            }
            // Procesar y establecer la hora con los valores recibidos
            // Usa pInput->frame->ZW_Common.cmdClass + 2 para weekday
            // Usa pInput->frame->ZW_Common.cmdClass + 3 para hour
            // Usa pInput->frame->ZW_Common.cmdClass + 4 para minute
            break;

        default:
            return RECEIVED_FRAME_STATUS_NO_SUPPORT;
    }

    if (responseExpected && pOutput->length < 1) {
        return RECEIVED_FRAME_STATUS_FAIL;
    }

    return RECEIVED_FRAME_STATUS_SUCCESS;
}

REGISTER_CC_V5(COMMAND_CLASS_CLOCK, CLOCK_VERSION_V1, CC_Clock_handler, NULL, NULL, NULL, 0, NULL, NULL);
