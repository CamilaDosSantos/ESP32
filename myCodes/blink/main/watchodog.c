#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
void task1 (void *param) {
while(1) {
}
}
void app_main(void) {
xTaskCreate(&task1, "task1", 2048, NULL, 1, NULL);//não ta fazendo nada
}