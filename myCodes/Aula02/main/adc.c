#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
void app_main()
{
adc1_config_width(ADC_WIDTH_12Bit);
adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_11db);
while(1)
{
int val = adc1_get_raw(ADC1_CHANNEL_6);
printf("value is %d\n", val);
vTaskDelay(pdMS_TO_TICKS(1000));/*delay de 1 segundo*/
}
}