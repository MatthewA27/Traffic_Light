#include <stdio.h>
#include "pico/stdlib.h" // Calls Library

#define GREEN_LED 16
#define YELLOW_LED 14
#define RED_LED 15
#define BUTTON_PIN 17
volatile bool pedestrian_request = false;

void button_callback(uint gpio, uint32_t events) {
    pedestrian_request = true;
}

void green_light() {
    gpio_put(GREEN_LED, 1);
    gpio_put(YELLOW_LED, 0); 
    gpio_put(RED_LED, 0); 
}

void yellow_light() {
    gpio_put(GREEN_LED, 0);
    gpio_put(YELLOW_LED, 1); 
    gpio_put(RED_LED, 0);
}

void red_light() {
    gpio_put(GREEN_LED, 0);
    gpio_put(YELLOW_LED, 0); 
    gpio_put(RED_LED, 1);
}

void cross_light() {
    gpio_put(GREEN_LED, 1);
    gpio_put(YELLOW_LED, 1); 
    gpio_put(RED_LED, 1);
}

void initialize_hardware() {
    gpio_init(BUTTON_PIN);
    gpio_init(GREEN_LED);
    gpio_init(YELLOW_LED);
    gpio_init(RED_LED);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
    gpio_set_dir(YELLOW_LED, GPIO_OUT);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_pull_up(BUTTON_PIN);

    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);

}

int main() // Main Function
{
    stdio_init_all();

    initialize_hardware();

    while (true) {
        if (gpio_get(BUTTON_PIN) == 0) {
            pedestrian_request = true;
        }

        green_light();
        sleep_ms(5000);
        yellow_light();
        sleep_ms(2000);
        red_light();
        if (pedestrian_request) {
            cross_light();
        }
        sleep_ms(5000);
        pedestrian_request = false;
    }
}
