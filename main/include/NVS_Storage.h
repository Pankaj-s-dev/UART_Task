#ifndef NVS_STORAGE_H
#define NVS_STORAGE_H

#include <string>
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

class NVS_Storage {
private:
    const char *_nvs_namespace;
    const char *_nvs_key;
    nvs_handle_t _nvs_handle;
    const char *TAG;

public:
    NVS_Storage(const char *nvs_namespace, const char *key, const char *TAG_FOR_LOG);

    void write(uint8_t *data);
    void print_from_storage();
    void erase();
};

#endif // NVS_STORAGE_H
