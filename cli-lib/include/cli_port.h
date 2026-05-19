/*
 * cli_port.h
 *
 * Hardware Abstraction Layer (HAL) para CLI.
 *
 * Este archivo define la INTERFAZ que cada plataforma debe implementar.
 * La librería CLI usa únicamente estas funciones para leer/escribir,
 * sin conocer el hardware subyacente.
 *
 * Para portar a una nueva plataforma, crear un archivo cli_port_XXX.c
 * que implemente las tres funciones declaradas aquí.
 *
 * Plataformas disponibles:
 *   cli_port_pico.c      → Raspberry Pi Pico (USB-CDC / UART)
 *   cli_port_pic.c       → Microcontroladores PIC (UART hardware)
 *   cli_port_netburner.c → NetBurner (serial API propia)
 *   cli_port_pc.c        → PC Linux / Windows (stdin no bloqueante)
 */

#ifndef INC_CLI_PORT_H_
#define INC_CLI_PORT_H_

#include <stdbool.h>

/**
 * @brief  Indica si hay al menos un carácter disponible para leer.
 *         Esta función NO debe bloquearse nunca. Debe retornar de forma
 *         inmediata con true o false.
 *
 * @return true  - hay un carácter listo; llamar a CLI_Port_GetChar() es seguro.
 * @return false - no hay datos disponibles en este momento.
 */
bool CLI_Port_IsCharAvailable(void);

/**
 * @brief  Lee y retorna un carácter del canal de entrada.
 *         Solo debe llamarse después de que CLI_Port_IsCharAvailable()
 *         haya retornado true.
 *
 * @return Carácter leído (0–255 como int).
 */
int CLI_Port_GetChar(void);

/**
 * @brief  Envía una cadena de texto por el canal de salida.
 *         Se provee como alternativa a printf() para plataformas donde
 *         la librería estándar no está disponible o printf() es costoso.
 *
 * @param  str  Cadena terminada en '\0' a transmitir.
 */
void CLI_Port_Print(const char *str);

#endif /* INC_CLI_PORT_H_ */
