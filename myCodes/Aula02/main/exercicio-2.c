
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define PIN_BUTTON 15
#define PIN_LED 23

void app_main()
{
    gpio_pad_select_gpio(PIN_LED);                 // define o pino
    gpio_set_direction(PIN_LED, GPIO_MODE_OUTPUT); // modo do pino -saida

    gpio_pad_select_gpio(PIN_BUTTON);                // define o pino
    gpio_set_direction(PIN_BUTTON, GPIO_MODE_INPUT); // modo do pino -entrada

    gpio_pulldown_en(PIN_BUTTON); // liga o pulldown
    gpio_pullup_dis(PIN_BUTTON);  // desliga o pullup

    bool ValorBut = 0; // valor de entrada

    while (1)
    {
        if (gpio_get_level(PIN_BUTTON))
        {
            ValorBut =
                !ValorBut; // o valor dele vai ser igual a ele ao contrario
            vTaskDelay(pdMS_TO_TICKS(250));
        }

        switch (ValorBut)
        {
        case 0: // fazendo o led piscar ex: o tempo que faz ele piscar
            gpio_set_level(PIN_LED, 1);     // liga
            vTaskDelay(pdMS_TO_TICKS(250)); // um tempo de espera
            gpio_set_level(PIN_LED, 0);     // desliga
            vTaskDelay(pdMS_TO_TICKS(250)); // tempo
            break;
        case 1:
            gpio_set_level(PIN_LED, 1);
            break;

        default:
            break;
        }
    }
}