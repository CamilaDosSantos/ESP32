#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void task1 (void *param) {
    while(1) {
    //     vTaskDelay(pdMS_TO_TICKS(1000)); // delay de 1 segundo
    //     vTaskDelay(1000/portTICK_PERIOD_MS); // delay de 1 segundo
    }
}

void app_main(void) {
    xTaskCreate(&task1, "task1", 2048, NULL, 0, NULL);
}