#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "driver/uart.h"
#include "FAT_Storage.h"
#include "NVS_Storage.h"

#define USE_NVS 1 // 1 for NVS and 0 for FAT
#define TAG "MAIN"

#define UART_NUM UART_NUM_0
#define BUF_SIZE 1024
#define TXD_PIN GPIO_NUM_43
#define RXD_PIN GPIO_NUM_44
#define RTS GPIO_NUM_15
#define CTS GPIO_NUM_16
#define READ_TIMEOUT_MS 1000

uint32_t bits_received=0;
uint32_t data_rate_bps=0; 

void print_data_rate(float time_interval, uint32_t bytes_received) {

    bits_received = bytes_received * 8;
    printf("bits_received: %ld bR and time interval %f\n", bits_received , time_interval);

    data_rate_bps = bits_received / time_interval ;

    printf("Speed: %ld bps\n", data_rate_bps);

}

void nvs_init(){
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

void UART_CONFIG(){
    uart_config_t UART_Init = {
        .baud_rate = 2400,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
        .rx_flow_ctrl_thresh = 0  
    };
    uart_driver_install(UART_NUM, BUF_SIZE, BUF_SIZE, 0, NULL, 0);
    uart_param_config(UART_NUM, &UART_Init);
    uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, RTS, CTS);
}

void UART_RECEIVE_TASK(void *arg) {
    uint32_t len = 0;
    ESP_LOGI(TAG, "Inside UART_RECEIVE_TASK");

    if (USE_NVS)
    {
        uint8_t data[1024]; 
        NVS_Storage *NVS_local = (NVS_Storage *)arg;
        
        while (1) {
            len = uart_read_bytes(UART_NUM, data, sizeof(data), pdMS_TO_TICKS(READ_TIMEOUT_MS));
            if (len > 0) {
                
                NVS_local->write(data);  

                if (data[len-1] == '\n') {
                    
                        ESP_LOGI(TAG, "Data received.");
                        NVS_local->print_from_storage();
                        NVS_local->erase();
                    }
            if (len == 0) {
                vTaskDelay(pdMS_TO_TICKS(500));
            }
            }
        }
    }
    
    if (!USE_NVS){
        uint8_t data[100]; 

        FAT_Storage *FAT_local = (FAT_Storage *)arg;

        ESP_LOGI(TAG, "Inside UART_RECEIVE_TASK FAT Local");
        while (1) {

            len = uart_read_bytes(UART_NUM, data, sizeof(data), pdMS_TO_TICKS(READ_TIMEOUT_MS));
            if (len > 0) {
                FAT_local->append_to_file((const char *)data, len);  
                if (data[len-1] == '\n') {
                    ESP_LOGI(TAG, "Data received.");
                    FAT_local->print_file_content();
                }
 
            if (len == 0) {
                vTaskDelay(pdMS_TO_TICKS(500));
            }
            }
        } 
    } 
}


extern "C" void app_main(void)
{   
    UART_CONFIG();
    
    if (USE_NVS){
        nvs_init();
        NVS_Storage NVS_system("UART", "data", "NVS_Storage_Retraval");
        // NVS_system.write("Hello World");
        // NVS_system.print_from_storage();
        xTaskCreate(UART_RECEIVE_TASK, "UART_RECEIVE_TASK", 1024 * 4, &NVS_system, 10, NULL);
        while (1)
        {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }

    if (!USE_NVS){
        FAT_Storage FAT("data.txt", "/uart", "storage");
        xTaskCreate(UART_RECEIVE_TASK, "UART_RECEIVE_TASK", 1024 * 4, &FAT, 10, NULL);
        while (1)
        {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        
    }
}
