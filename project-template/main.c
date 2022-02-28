#include <stdio.h>          //printf
#include "pico/stdlib.h"    //pico libraries

int main()
{
    const uint led_pin = 25;    //Pin Led on Raspberry Pi Pico board

    // Initialize Pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    //Put your setup here
    //setup();

    // Initialize chosen serial port
    stdio_init_all();           //We need to initialized the serial port    

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
    }
}