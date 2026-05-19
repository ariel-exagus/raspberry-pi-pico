/*
 * main.c
 *
 * Ejemplo de uso de la librería CLI con Raspberry Pi Pico.
 * CLI_Task() es no bloqueante: el loop principal puede hacer otras
 * tareas (blink, sensores, etc.) sin que la CLI los interrumpa.
 */

#include "cli.h"
#include "pico/stdlib.h"

const uint LED_PIN = 25;            /* LED onboard de la Raspberry Pi Pico */

bool led_enable = true;

/* Prototipos de comandos */
void cmd_hello(int argc, char *argv[]);
void cmd_echo(int argc, char *argv[]);
void cmd_cli_version(int argc, char *argv[]);
void cmd_led(int argc, char *argv[]);
void cmd_echo_mode(int argc, char *argv[]);

int main(void)
{
    /* Inicializar GPIO del LED */
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    /* Inicializar puerto serie (USB-CDC o UART según CMakeLists) */
    stdio_init_all();

    /* Registrar comandos ANTES de llamar CLI_Init() */
    CLI_RegisterCommand("hello",       cmd_hello,       "Print a test message");
    CLI_RegisterCommand("echo",        cmd_echo,        "Repeat the arguments provided");
    CLI_RegisterCommand("cli_version", cmd_cli_version, "Print the CLI version");
    CLI_RegisterCommand("led",         cmd_led,         "LED control: led <on|off>");
    CLI_RegisterCommand("echo_mode", cmd_echo_mode, "Enable/disable input echo: echo_mode <on|off>");

    /* Mostrar banner y lista de comandos */
    CLI_Init();

    /* Loop principal — ninguna tarea bloquea a las demás */
    while (1)
    {
        /*
         * CLI_Task() procesa los caracteres disponibles y retorna
         * inmediatamente si no hay datos. No bloquea el loop.
         */
        CLI_Task();

        /*
         * Otras tareas del sistema pueden ejecutarse aquí sin demora.
         * El blink ya no interfiere con la recepción de comandos.
         */
        if(led_enable){
            gpio_put(LED_PIN, true);
            sleep_ms(500);
            gpio_put(LED_PIN, false);
            sleep_ms(500);
        }
    }

    return 0;
}

/* ------------------------------------------------------------------ */
/*  Implementación de comandos                                          */
/* ------------------------------------------------------------------ */

void cmd_hello(int argc, char *argv[])
{
    printf("Hello, World!\r\n");
}

void cmd_echo(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\r\n");
}

void cmd_cli_version(int argc, char *argv[])
{
    printf("CLI version: v1.2.0\r\n");
}

void cmd_led(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: led <on|off>\r\n");
        return;
    }

    if (strcmp(argv[1], "on") == 0) {
        //gpio_put(LED_PIN, true);
        led_enable = true;
        printf("LED ON\r\n");
    } else if (strcmp(argv[1], "off") == 0) {
        //gpio_put(LED_PIN, false);
        led_enable = false;
        printf("LED OFF\r\n");
    } else {
        printf("Invalid argument. Usage: led <on|off>\r\n");
    }
}

void cmd_echo_mode(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: echo_mode <on|off>\r\n");
        return;
    }
    if (strcmp(argv[1], "on") == 0) {
        CLI_SetEcho(true);
        printf("Echo enabled\r\n");
    } else if (strcmp(argv[1], "off") == 0) {
        CLI_SetEcho(false);
        printf("Echo disabled\r\n");
    } else {
        printf("Invalid argument. Usage: echo_mode <on|off>\r\n");
    }
}
