#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
const char *TAG = "tasks.c";
void task1(void *param)
{
    while (true)
    {
        ESP_LOGI(TAG, "core %d/line %d/%s/reading temperature/%d",
                 xPortGetCoreID(), __LINE__, __func__,
                 uxTaskGetStackHighWaterMark(NULL));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void task2()
{
    while (true)
    {
        ESP_LOGW(TAG, "core %d/line %d/%s/reading humidity/%d",
                 xPortGetCoreID(), __LINE__, __func__,
                 uxTaskGetStackHighWaterMark(NULL));
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    ESP_LOGI(TAG, "core %d/line %d/%s/starting ", xPortGetCoreID(), __LINE__,
             __func__);
    task1(NULL);
    task2(NULL);

    // xTaskCreate(&task1, " temperature reading", 2048, NULL, 2, NULL);
    // xTaskCreate(&task2, " temperature reading", 2048, NULL, 2, NULL);
   xTaskCreatePinnedToCore(&task1, " temperature reading", 2048, NULL, 2, NULL);
    xTaskCreatePinnedToCore(&task2, " temperature reading", 2048, NULL, 2, APP_CPU_NUM);
    
}



























































































































































