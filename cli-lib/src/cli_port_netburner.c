/*
 * cli_port_netburner.c
 *
 * Implementación de la HAL para plataformas NetBurner (MOD5270, SB700, etc.).
 * Canal de comunicación: UART serial vía API de NetBurner.
 *
 * La API de NetBurner provee charavail() que retorna la cantidad de
 * caracteres disponibles en el buffer sin bloquear, lo que se mapea
 * directamente al contrato de CLI_Port_IsCharAvailable().
 *
 * Headers requeridos de NetBurner SDK:
 *   #include <utils.h>    → charavail(), getchar()
 *   #include <stdio.h>    → printf()
 */

#include "../include/cli_port.h"
#include <utils.h>
#include <stdio.h>

bool CLI_Port_IsCharAvailable(void)
{
    /*
     * charavail() retorna la cantidad de bytes disponibles en el buffer
     * de recepción serie. Es no bloqueante por diseño en NetBurner.
     */
    return (charavail() > 0);
}

int CLI_Port_GetChar(void)
{
    /*
     * getchar() en NetBurner lee del puerto serie configurado.
     * Solo llamar cuando charavail() > 0 para evitar bloqueo.
     */
    return getchar();
}

void CLI_Port_Print(const char *str)
{
    printf("%s", str);
}
