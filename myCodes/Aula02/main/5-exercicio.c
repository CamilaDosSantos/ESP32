/*

Faça um monitor de bateria de Li Íon.
• Crie um circuito com um potenciômetro que simule os valores da
bateria: 2,8V a 4,2V.
• Com o ESP32 faça a leitura desses valores e acenda os leds de
acordo com a tabela
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"



// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.



void app_main(void) {
    while(1) {
        int sensor = hall_sensor_read();
        
        printf("Valor da leitura do sensor: %d\n", sensor);
        vTaskDelay(pdMS_TO_TICKS(500)); // delay
    }
}

