// 1-Exercicio
// Faça um programa que simule um chat pela serial:
// Fonte: Comando para limpar uma linha do terminal
// • As mensagens deverão aparecer na tela
// como uma conversa de WhatsApp;
// • Utilize o programa "Entrada de teclado" como base para criar as
// mensagens a serem enviadas;
// • Você deverá conectar seu ESP32
// com o ESP32 de um colega por
// meio da UART para vocês trocarem
// mensagens e status pela serial
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"
#define RED "\x1b[31m" // cor 
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define PURPLE "\x1b[35m"
#define LIGHT_BLUE "\x1b[36m"
#define RESET "\x1b[0m"


static const int RX_BUF_SIZE = 1024;
#define PURPLE
#define RESET
#define TXD_PIN (GPIO_NUM_17) // pinos definidos tx
#define RXD_PIN (GPIO_NUM_16) // pinos definidos rx

void init(void)
{

    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    // We won't use a buffer for sending data.
    uart_driver_install(UART_NUM_1, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE,
                 UART_PIN_NO_CHANGE);
}

int sendData(const char *logName, const char *data)
{
    const int len = strlen(data);
    const int txBytes = uart_write_bytes(UART_NUM_1, data, len);
    return txBytes;
}

static void tx_task(void *arg)
{
 while(1){
    static const char *TX_TASK_TAG = "TX_TASK";
    esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);
    char c = 0;
    char *str = (char *)malloc(100);

    // zerando conteudo de str
    memset(str, 0, 100);


    while (c != '\n') // anter \n enquanto não receber o enter
    {
        // Recebe dado pela serial
        c = getchar();

        // Caso a tecla seja "backspace"
        if (c == 0x08) // aquela teclaque vai apagando no teclado
        {
            c = '\0';
            // Apaga o último caracter da string
            str[((strlen(str) - 1) > 0) ? strlen(str) - 1 : 0] = c;

            // Apaga o conteúdo da linha no terminal
            printf("\x1b[2K");

            // Imprime conteúdo de str no terminal
            printf("\rDigite: %.*s", strlen(str), str);
        }
        // Caso seja caracter válido
        else if ((c >= 0x20) && (c <= 0x7e))
        {
            // Insere caracter na ultima posição de str
            str[strlen(str)] = c;

            // Apaga o conteúdo da linha no terminal
            printf("\x1b[2K");

            // Imprime conteúdo de str no terminal
            printf("\rDigite: %.*s", strlen(str), str);
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    // Apaga o conteúdo da linha no terminal
    printf("\x1b[2K");
    // printf("%s", str);
     printf("\rCamila: %s\n", str);
    sendData(TX_TASK_TAG, str);
}
}
static void rx_task(void *arg)
{
    static const char *RX_TASK_TAG = "CAMILA";
    esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    uint8_t *data = (uint8_t *)malloc(RX_BUF_SIZE + 1);
    while (1)
    {
        const int rxBytes = uart_read_bytes(UART_NUM_1, data, RX_BUF_SIZE,
                                            1000 / portTICK_RATE_MS);
        if (rxBytes > 0)
        {
            data[rxBytes] = 0;
            ESP_LOGE(RX_TASK_TAG, "%s", data);
            // printf("\rLucas: %s\n", data);
        }
    }
    free(data);
}

void app_main(void)
{

    init();
    xTaskCreate(rx_task, "uart_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES,
                NULL);
    xTaskCreate(tx_task, "uart_tx_task", 1024 * 2, NULL,
                configMAX_PRIORITIES - 1, NULL);
}
