/*
 * cli_port_pic.c
 *
 * Implementación de la HAL para microcontroladores PIC.
 * Canal de comunicación: UART hardware (EUSART).
 *
 * Los nombres de registros y bits corresponden a PIC18Fxxxx con XC8.
 * Adaptar según el modelo de PIC específico (PIC16, PIC32, etc.).
 *
 * Registros utilizados:
 *   PIR1bits.RCIF  → Flag: dato recibido en UART (1 = hay dato)
 *   RCSTAbits.OERR → Flag: overrun error (limpiar para recuperar UART)
 *   RCREG          → Registro de recepción UART (leer limpia el flag)
 *   TXSTAbits.TRMT → Flag: buffer TX vacío (1 = listo para enviar)
 *   TXREG          → Registro de transmisión UART
 */

#include "../include/cli_port.h"

/* ------------------------------------------------------------------ */
/*  Incluir el header de tu dispositivo PIC específico, por ejemplo:   */
/*  #include <xc.h>              (compilador XC8/XC16/XC32)            */
/*  #include <p18f4550.h>        (device-specific)                     */
/* ------------------------------------------------------------------ */
#include <xc.h>

bool CLI_Port_IsCharAvailable(void)
{
    /* RCIF se pone en 1 automáticamente cuando llega un byte al RCREG */
    return (bool)PIR1bits.RCIF;
}

int CLI_Port_GetChar(void)
{
    /* Verificar y limpiar error de overrun si ocurrió */
    if (RCSTAbits.OERR) {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    /* Leer RCREG limpia automáticamente el flag RCIF */
    return (int)RCREG;
}

void CLI_Port_Print(const char *str)
{
    while (*str != '\0') {
        /* Esperar a que el buffer de transmisión esté libre */
        while (!TXSTAbits.TRMT);
        TXREG = (unsigned char)(*str++);
    }
}
