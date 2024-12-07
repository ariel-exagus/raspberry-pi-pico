#include "cli.h"
#include "pico/stdlib.h"    //pico libraries

const uint led_pin = 25;    //Pin Led on Raspberry Pi Pico board

//comandos
void cmd_hello(int argc, char *argv[]);
void cmd_echo(int argc, char *argv[]);
void cmd_cli_version(int argc, char *argv[]);
void cmd_led(int argc, char *argv[]);

int main()
{
    

    // Initialize Pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    //Put your setup here
    //setup();

    // Initialize chosen serial port
    stdio_init_all();           //We need to initialized the serial port

    // Registrar comandos
    CLI_RegisterCommand("hello", cmd_hello, "Print a test message");
    CLI_RegisterCommand("echo", cmd_echo, "Repeat the arguments provided");
    // Colocar la lista de comandos propios
    CLI_RegisterCommand("cli_version", cmd_cli_version, "Prints the CLI version");
    CLI_RegisterCommand("led", cmd_led, "LED status control (on/off)");

    // Inicializar CLI
    CLI_Init();
    

    // loop forever to blink led
    while(1)
    {
        // Example of Blink LED
        printf("Template project!\r\n");
        gpio_put(led_pin, true);
        sleep_ms(1000);
        gpio_put(led_pin, false);
        sleep_ms(1000);

        // Put your code Here
        CLI_Task();
    }

    return 0;
}

// Ejemplo de comandos
void cmd_hello(int argc, char *argv[]) {
    printf("Hello World! - test command\n");
}

void cmd_echo(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
}

// Comandos definidos por el usuario
void cmd_cli_version(int argc, char *argv[])
{
    printf("CLI version: v1.1.0\n");
}

void cmd_led(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Use: led <on|off>\n");
        return;
    }

    if (strcmp(argv[1], "on") == 0) {
        printf("LED_ON\n");
        gpio_put(led_pin, true);
    } else if (strcmp(argv[1], "off") == 0) {
        printf("LED_OFF\n");
        gpio_put(led_pin, false);
    } else {
        printf("Invalid argument. Use: led <on|off>\n");
    }
}

