#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "max6675.h"
#include "hardware/pwm.h"

void setup_pwm(uint pwmset) {
// Configuro el PWM en el numero de pin que indique GPIO 
gpio_set_function(pwmset, GPIO_FUNC_PWM); 
// Obtengo el numero de slice para ese GPIO 
uint8_t slice = pwm_gpio_to_slice_num(pwmset); 
// Obtengo una configuracion por defecto de PWM 
pwm_config config = pwm_get_default_config(); 
// Divido los 125 MHz de clock de la Pico por 125 
// para tener un clock de 1 MHz 
pwm_config_set_clkdiv(&config, 125.0); 
// Cambio el wrap a 50000 para tener una frecuencia 
// de PWM de 50 ms (wrap / fclk) 
pwm_config_set_wrap(&config, 50000); 
// Habilito el PWM 
pwm_init(slice, &config, true); 
// Configuro la salida de PWM en el GPIO al 
// 50% de actividad (level / wrap) 
pwm_set_gpio_level(pwmset, 25000); 
}


int main(void) {
 

    stdio_init_all();
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);
    //inicializo los pines y los selecciono como outputs
    setup_pwm(16);
   
    while (true) {

        float temperatura = max6675_get_temp_c();
        uint16_t pote_val = adc_read();
        uint16_t esc_pot = pote_val * 200.0 / 4095.0;
        uint16_t dif = esc_pot-temperatura;
        uint16_t prop =(dif*562)+5000;

        if(dif >= 100) {
            // PWM 100%
        pwm_set_gpio_level(0,50000);
        }
        else if(dif <= 100 && dif >=  20) {
            // PWM proporcional
        pwm_set_gpio_level(0,prop);
        }
        else if(dif >=  20) {
            // PWM es minimo
        pwm_set_gpio_level(0,5000);
        }

      
    }
}
