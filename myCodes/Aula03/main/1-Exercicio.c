/*1. Faça um programa, utilizando tasks, que ao manter o botão
pressionado o LED pisca em uma frequência de 10 Hz e quando
solto em 2 Hz*/

#define PIN_BUTTON 15
#define PIN_LED 23
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/semphr.h"

#define PIN_BUTTON 15
#define PIN_LED 23 /* mantem o botão precionado "gpio_get_level(PIN_BUTTON_)"*/
xSemaphoreHandle mutexBus; 
int counter = 0;
int level = 0;
const char* TAG ="1-Exercicio";

void task1(void *param)
{
  
    while (true)
    {
       
        int level = gpio_get_level(PIN_BUTTON);
        if(level == 1)
            {
                xSemaphoreTake(mutexBus, 0);
                counter = 1;
                xSemaphoreGive(mutexBus);       
            }
        else
        {
            xSemaphoreTake(mutexBus, 0);
            counter = 0;
            xSemaphoreGive(mutexBus);       
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void task2(void *param)
{
   bool isOn = 0;
    while (true)
    {
       isOn = !isOn;
        if(counter ==1)
            {

                
            gpio_set_level(PIN_LED, isOn);     // ligar led
            vTaskDelay(pdMS_TO_TICKS(50));
        
            }
        else
        {
            gpio_set_level(PIN_LED, isOn); // liga o led
            vTaskDelay(pdMS_TO_TICKS(250));
           
        }
    }
    vTaskDelete(NULL);
}



void app_main()
{
    printf("LED --");
    ESP_LOGI(TAG, "Satrting!");
    gpio_pad_select_gpio(PIN_LED);                 // define o pino
    gpio_set_direction(PIN_LED, GPIO_MODE_OUTPUT); // modo do pino -saida

    gpio_pad_select_gpio(PIN_BUTTON);                // define o pino
    gpio_set_direction(PIN_BUTTON, GPIO_MODE_INPUT); // modo do pino -entrada

    gpio_pulldown_en(PIN_BUTTON);
    gpio_pullup_dis(PIN_BUTTON);

     mutexBus = xSemaphoreCreateMutex();

     xTaskCreate(&task1, "temperature reading", 2048, NULL, 2, NULL);
     xTaskCreate(&task2, "humidity reading", 2048, NULL, 2, NULL);
    }


