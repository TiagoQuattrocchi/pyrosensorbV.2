#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
// defino los gpio pins para los LEDs
#define LED_verde 13
#define LED_amarillo 14
#define LED_rojo 15


int main(void) {
 

    stdio_init_all();
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);
    //inicializo los pines y los selecciono como outputs
    gpio_init(LED_PIN1);
    gpio_init(LED_PIN2);
    gpio_init(LED_PIN3);
    gpio_set_dir(LED_PIN1, GPIO_OUT);
    gpio_set_dir(LED_PIN2, GPIO_OUT);
    gpio_set_dir(LED_PIN3, GPIO_OUT);
    
    while (true) {
    uint16_t pote_val = adc_read();
        uint16_t esc_pot = pote_val * 200.0 / 4095.0;
       
        // si la temperatura se encuentra entre el valor de pot +- 20 grados enciende led verde
        if (max6675_get_temp_c >= esc_pot-20 && max6675_get_temp_c <= esc_pot+20 ) {
            gpio_put(LED_verde, 1);
        } else {
            gpio_put(LED_verde, 0);
        }
         // si la temperatura se encuentra entre el valor de pot +- 20 grados enciende led rojo
                
        if (max6675_get_temp_c >= esc_pot+20) {
            gpio_put(LED_rojo, 1);
        } else {
            gpio_put(LED_rojo, 0);
        }
         // si la temperatura se encuentra debajo del valor de pot - 20 grados enciende led amarillo
       
        if (max6675_get_temp_c <= esc_pot-20) {
            gpio_put(LED_amarillo, 1);
        } else {
            gpio_put(LED_amarillo, 0);
        }
    }
}
