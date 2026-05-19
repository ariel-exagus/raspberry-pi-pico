/*
 * cli.h
 *
 *  Created on: 5 dec 2024
 *      Author: Ariel
 */

#ifndef INC_CLI_H_
#define INC_CLI_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COMMANDS 10
#define MAX_INPUT_LENGTH 64
#define NEWLINE "\r\n"

// Define messages
#define UNKNOWN_CMD_MSG "--------------------------------------------\n"\
                        "Unknown command. List of available commands:\n"

#define END_CMD_MSG     "--------------------------------------------\n"
#define CLI_PROMPT        "> "

// Tipo de función para comandos
typedef void (*CommandFunction)(int argc, char *argv[]);

// Estructura de un comando
typedef struct {
    const char *name;
    CommandFunction function;
    const char *description;
} CLI_Command;


// Prototipos

/**
 * @brief  Inicializa la CLI. Muestra el banner y la lista de comandos.
 *         Llamar una vez al inicio, luego de registrar los comandos.
 */
void CLI_Init(void);

/**
 * @brief  Tarea principal de la CLI. NO bloqueante.
 *         Procesa todos los caracteres disponibles en el buffer de entrada
 *         y retorna inmediatamente si no hay datos.
 *         Debe llamarse periódicamente desde el loop principal.
 */
void CLI_Task(void);

/**
 * @brief  Registra un nuevo comando en la CLI.
 * @param  name         Nombre del comando (string que el usuario escribe).
 * @param  function     Función a ejecutar cuando se recibe el comando.
 * @param  description  Descripción corta (se muestra en la ayuda).
 */
void CLI_RegisterCommand(const char *name, CommandFunction function, const char *description);

void CLI_SetEcho(bool enable);

#endif /* INC_CLI_H_ */