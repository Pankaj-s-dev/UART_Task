#include "NVS_Storage.h"

esp_err_t err;

NVS_Storage::NVS_Storage(const char *nvs_namespace, const char *key, const char *TAG_FOR_LOG): 
    _nvs_namespace(nvs_namespace), _nvs_key(key), TAG (TAG_FOR_LOG) {}

void NVS_Storage::write( uint8_t *data) {

    const char *incooming_data = (const char *)data;

    err = nvs_open(_nvs_namespace, NVS_READWRITE, &_nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error opening NVS handle!");
        return;
    }

    err = nvs_set_str(_nvs_handle, _nvs_key, incooming_data);

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Data saved successfully!");
    } else {
        ESP_LOGE(TAG, "Failed to save data!");
    }

    err = nvs_commit(_nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to commit changes!");
    }

    nvs_close(_nvs_handle);
}

void NVS_Storage::print_from_storage() {

    size_t buffer_size = 0;  

    err = nvs_open(_nvs_namespace, NVS_READONLY, &_nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error opening NVS handle!");
        return;
    }

    err = nvs_get_str(_nvs_handle, _nvs_key, NULL, &buffer_size);
    if (err != ESP_OK) {
        if (err == ESP_ERR_NVS_NOT_FOUND) {
            ESP_LOGW(TAG, "Data not found!");
        } else {
            ESP_LOGE(TAG, "Error getting string size!");
        }
        nvs_close(_nvs_handle);
        return;
    }

    char UART_Data[buffer_size];

    err = nvs_get_str(_nvs_handle, _nvs_key, &UART_Data[0], &buffer_size);
    if (err == ESP_OK) {
        printf( "%s", UART_Data);
    } else {
        ESP_LOGE(TAG, "Error reading string!");
    }

    nvs_close(_nvs_handle);
}

void NVS_Storage::erase() {
    err = nvs_open(_nvs_namespace, NVS_READWRITE, &_nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error opening NVS handle!");
        return;
    }

    err = nvs_erase_key(_nvs_handle, _nvs_key);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Key erased successfully!");
    } else {
        ESP_LOGE(TAG, "Failed to erase key!");
    }

    nvs_commit(_nvs_handle);

    nvs_close(_nvs_handle);
}
