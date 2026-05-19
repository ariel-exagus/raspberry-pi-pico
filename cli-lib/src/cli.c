/*
 * cli.c
 *
 * Implementación de la librería CLI genérica.
 * Usa la HAL (cli_port.h) para toda interacción con el hardware,
 * lo que la hace independiente de la plataforma.
 */

#include "../include/cli.h"
#include "../include/cli_port.h"

/* Lista de comandos registrados */
static CLI_Command commandList[MAX_COMMANDS];
static int         commandCount = 0;

/* Buffer de entrada y su índice */
static char inputBuffer[MAX_INPUT_LENGTH];
static int  inputIndex = 0;
static bool echoEnabled = false;

/* ------------------------------------------------------------------ */
/*  Funciones internas                                                  */
/* ------------------------------------------------------------------ */

static void PrintCommandList(void)
{
    for (int i = 0; i < commandCount; i++) {
        CLI_Port_Print("  ");
        CLI_Port_Print(commandList[i].name);
        CLI_Port_Print(" - ");
        CLI_Port_Print(commandList[i].description);
        CLI_Port_Print("\r\n");
    }
}

static void PrintUnknownCommandMsg(void)
{
    CLI_Port_Print(UNKNOWN_CMD_MSG);
    PrintCommandList();
    CLI_Port_Print(END_CMD_MSG);
}

static void ProcessCommand(void)
{
    char *argv[MAX_COMMANDS];
    int   argc  = 0;

    /* Tokenizar la entrada separando por espacios */
    char *token = strtok(inputBuffer, " ");
    while (token != NULL && argc < MAX_COMMANDS) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (argc == 0) {
        PrintUnknownCommandMsg();
        return;
    }

    /* Buscar el comando en la lista y ejecutarlo */
    bool command_found = false;
    for (int i = 0; i < commandCount; i++) {
        if (strcmp(argv[0], commandList[i].name) == 0) {
            commandList[i].function(argc, argv);
            command_found = true;
            break;
        }
    }

    if (!command_found) {
        PrintUnknownCommandMsg();
    }
}

/* ------------------------------------------------------------------ */
/*  API pública                                                         */
/* ------------------------------------------------------------------ */

void CLI_Init(void)
{
    CLI_Port_Print("\r\n===== CLI v1.2.0 =====\r\n");
    CLI_Port_Print("Available commands:\r\n");
    PrintCommandList();
    CLI_Port_Print("\r\n");
    CLI_Port_Print(CLI_PROMPT);
}

/*
 * CLI_Task() — NO bloqueante.
 *
 * Procesa todos los caracteres que estén disponibles en este momento
 * y retorna inmediatamente cuando no hay más datos.
 * El loop principal puede seguir ejecutando otras tareas sin demora.
 */
void CLI_Task(void)
{
    while (CLI_Port_IsCharAvailable())          /* ← no bloquea */
    {
        int ch = CLI_Port_GetChar();

        if (ch == '\n' || ch == '\r') {
            /* Fin de línea: procesar el comando acumulado */
            inputBuffer[inputIndex] = '\0';
            CLI_Port_Print("\r\n");

            if (inputIndex > 0) {
                ProcessCommand();
            }

            inputIndex = 0;
            CLI_Port_Print(CLI_PROMPT);

        } else if (ch == '\b' || ch == 127) {
            /* Backspace: eliminar último carácter del buffer */
            if (inputIndex > 0) {
                inputIndex--;
                if (echoEnabled) CLI_Port_Print("\b \b");        /* borra el carácter en terminal */
            }

        } else if (inputIndex < MAX_INPUT_LENGTH - 1) {
            /* Carácter normal: agregar al buffer con eco local */
            inputBuffer[inputIndex++] = (char)ch;
            char echo[2] = {(char)ch, '\0'};
            if (echoEnabled) CLI_Port_Print(echo);

        } else {
            /* Buffer lleno */
            CLI_Port_Print("\r\nError: Command too long.\r\n");
            inputIndex = 0;
            CLI_Port_Print(CLI_PROMPT);
        }
    }
    /* Sin datos disponibles → retorna inmediatamente */
}

void CLI_RegisterCommand(const char *name, CommandFunction function, const char *description)
{
    if (commandCount < MAX_COMMANDS) {
        commandList[commandCount].name        = name;
        commandList[commandCount].function    = function;
        commandList[commandCount].description = description;
        commandCount++;
    } else {
        CLI_Port_Print("Error: Command list full.\r\n");
    }
}

void CLI_SetEcho(bool enable)
{
    echoEnabled = enable;
}
