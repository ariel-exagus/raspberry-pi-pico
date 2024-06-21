#include "pico/stdlib.h"
#include <iostream>

using namespace std;

int main()
{
    const uint led_pin = 25;
    
    // Initialize led pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);


    // Initialie chosen serial port
    stdio_init_all();       // We need to initialized the serial port

    // loop forever
    while(1)
    {
        gpio_put(led_pin, true);
        sleep_ms(1000);
        gpio_put(led_pin, false);
        sleep_ms(1000);

        // Put your code here
        cout << "It's me, your first program" << endl;
    }
    
    return 0;
}