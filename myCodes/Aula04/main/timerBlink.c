#include <stdio.h>// e um jeito novo de salvar as coisas em outros lugar o ponteiro recebemalloc  e esta alocando 32 bits  sempre que aloca voce desaloca 
#include <string.h>
#include "freertos/FreeRTOS.h" 
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_timer.h"
// não ta na aplication man e sim na callback quem ta digando e desligando é o callback 
#define PIN_LED 23 // porta no ESP 

esp_timer_handle_t blinkTimerHandler; // Blink timer handler.

void blinkTimerCallback(void* arg) // 
{
    static bool isOn = false;
    isOn = !isOn;
    gpio_set_level(PIN_LED, isOn);// seta o led pra ligar ou desligar mais se ofr igual ou diferente 
}

void app_main() 
{
    gpio_pad_select_gpio(PIN_LED); // liga o led 
    gpio_set_direction(PIN_LED, GPIO_MODE_OUTPUT);
    esp_err_t ret;

    esp_timer_create_args_t timer_args = { // argumentos timer  
        .callback = blinkTimerCallback,
        .arg = NULL,
        .name = "blink",
        .dispatch_method = ESP_TIMER_TASK,
    };
    
    esp_timer_create(&timer_args, &blinkTimerHandler);
    esp_timer_start_periodic(blinkTimerHandler, 100 * 1000);
    
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(3000)); // delay de 3000 mili segundos 
        esp_timer_stop(blinkTimerHandler); // 
        esp_timer_start_periodic(blinkTimerHandler, 200 * 1000);

        vTaskDelay(pdMS_TO_TICKS(3000));
        esp_timer_stop(blinkTimerHandler);
        esp_timer_start_periodic(blinkTimerHandler, 300 * 1000);
        
        vTaskDelay(pdMS_TO_TICKS(3000));
        esp_timer_stop(blinkTimerHandler);
        esp_timer_start_periodic(blinkTimerHandler, 400 * 1000);
        
        vTaskDelay(pdMS_TO_TICKS(3000));
        esp_timer_stop(blinkTimerHandler);
        esp_timer_start_periodic(blinkTimerHandler, 500 * 1000);
        
        vTaskDelay(pdMS_TO_TICKS(3000));
        esp_timer_stop(blinkTimerHandler);
        esp_timer_start_periodic(blinkTimerHandler, 100 * 1000);
    }
}
