#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define GPIO_OUTPUT 10  // GP8 como salida digital
#define GPIO_PWM 4  // GP0 para señal PWM

int main() {
    // Inicialización del sistema
    stdio_init_all();

    // Configuración del pin GP8 como salida digital
    gpio_init(GPIO_OUTPUT);
    gpio_set_dir(GPIO_OUTPUT, GPIO_OUT);

    // Configuración del pin GP0 como PWM
    gpio_set_function(GPIO_PWM, GPIO_FUNC_PWM);

    // Obtener el slice asociado al pin GP0
    uint slice_num = pwm_gpio_to_slice_num(GPIO_PWM);

    // Configurar el divisor de frecuencia para que el reloj PWM sea más lento
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0f); // Divisor de reloj

    // Aplicar la configuración al slice correspondiente
    pwm_init(slice_num, &config, true);

    // Configurar el duty cycle inicial al 50%
    pwm_set_gpio_level(GPIO_PWM, 0x7FFF);

    while (true) {
        // Alternar el estado del pin GP8 cada segundo
        gpio_put(GPIO_OUTPUT, 1);
        sleep_ms(500);
        

        // Cambiar el duty cycle del PWM (de 0% a 100%)
        for (uint16_t level = 0; level <= 0xFFFF; level += 0x0FFF) {
            pwm_set_gpio_level(GPIO_PWM, level);
            sleep_ms(100);
        }
    }
}
