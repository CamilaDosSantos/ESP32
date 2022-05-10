/*3-Faça um programa que a medida que o botão é
pressionado aumente a intensidade do LED ao atingir o valor
máximo volte a zero. Adicione 5 passos.*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "driver/dac.h"

#define PIN_BUTTON 15
#define PIN_LED 25

app_void()
{

    gpio_pad_select_gpio(PIN_LED);                 // define o pino
    gpio_set_direction(PIN_LED, GPIO_MODE_OUTPUT); // modo do pino -saida

    gpio_pad_select_gpio(PIN_BUTTON);                // define o pino
    gpio_set_direction(PIN_BUTTON, GPIO_MODE_INPUT); // modo do pino -entrada

    gpio_pulldown_en(PIN_BUTTON); // liga o pulldown
    gpio_pullup_dis(PIN_BUTTON);  // desliga o pullup

    bool button = 0;

    while (1)
    {
        if (gpio_get_level(PIN_BUTTON))
        {
        button +=1;
            vTaskDelay(pdMS_TO_TICKS(250));
        }
        switch(button)
        {
        case 1:
            dac_output_enable(DAC_CHANNEL_1);
            dac_output_voltage(DAC_CHANNEL_1, 150);
            break;

        case 2:
            dac_output_enable(DAC_CHANNEL_1);
            dac_output_voltage(DAC_CHANNEL_1, 140);
            break;

        case 3:
            dac_output_enable(DAC_CHANNEL_1);
            dac_output_voltage(DAC_CHANNEL_1, 130);
            break;

        case 4:
            dac_output_enable(DAC_CHANNEL_1);
            dac_output_voltage(DAC_CHANNEL_1, 120);
            break;

        case 5:
            dac_output_enable(DAC_CHANNEL_1);
            dac_output_voltage(DAC_CHANNEL_1, 110);
            break;

        default:
            button = 0;
            break;
        }
    }
}
