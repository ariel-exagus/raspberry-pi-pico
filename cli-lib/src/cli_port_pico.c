/*
 * cli_port_pico.c
 *
 * Implementación de la HAL para Raspberry Pi Pico.
 * Canal de comunicación: USB-CDC (o UART si se cambia la config del CMakeLists).
 *
 * Usa getchar_timeout_us(0) que retorna inmediatamente sin bloquear.
 * El "peek buffer" interno permite separar IsCharAvailable() de GetChar()
 * sin consumir el carácter dos veces.
 *
 * Para compilar este archivo, incluirlo en CMakeLists.txt:
 *   file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/cli_port_pico.c)
 */

#include "../include/cli_port.h"
#include "pico/stdlib.h"

/* ------------------------------------------------------------------ */
/*  Peek buffer de 1 carácter                                           */
/*                                                                      */
/*  Problema: getchar_timeout_us(0) consume el carácter al leerlo.     */
/*  Si lo llamamos en IsCharAvailable(), ya no está disponible para     */
/*  GetChar(). La solución es guardarlo en este buffer intermedio.      */
/* ------------------------------------------------------------------ */
static int  s_peek_char  = 0;
static bool s_peek_valid = false;

bool CLI_Port_IsCharAvailable(void)
{
    if (!s_peek_valid) {
        int c = getchar_timeout_us(0);          /* no bloqueante: timeout = 0 */
        if (c != PICO_ERROR_TIMEOUT) {
            s_peek_char  = c;
            s_peek_valid = true;
        }
    }
    return s_peek_valid;
}

int CLI_Port_GetChar(void)
{
    if (s_peek_valid) {
        s_peek_valid = false;
        return s_peek_char;
    }
    /* Fallback: si se llama sin verificar antes */
    return getchar_timeout_us(0);
}

void CLI_Port_Print(const char *str)
{
    /* printf en Pico envía por el canal habilitado (USB-CDC o UART) */
    printf("%s", str);
}
