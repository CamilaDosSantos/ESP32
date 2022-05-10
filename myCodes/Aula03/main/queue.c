#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
xQueueHandle queue;
void sender(void *params)
{
    int count = 0;
    while (true)
    {
        count++;
        if (xQueueSend(queue, &count, 10) != pdTRUE)
        {
            printf("Queue FULL\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void receiver(void *params)
{
    while (true)
    {
        int rxInt;
        if (xQueueReceive(queue, &rxInt, 0) == pdTRUE)
        {
            printf("received %d\n", rxInt);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void app_main(void)
{
    queue = xQueueCreate(3, sizeof(int));// define o tamnho da fila de 3 c
    xTaskCreate(&sender, "send", 2048, NULL, 2, NULL);
    xTaskCreate(&receiver, "receive", 2048, NULL, 1, NULL);
} 