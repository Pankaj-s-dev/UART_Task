#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "esp_err.h"
#include "esp_partition.h"
#include "esp_system.h"
#include "esp_log.h"
#include <string>
#include <iostream>
#include <stdio.h>

class FAT_Storage{
    private:
        const char *_file_name;
        const char *_Partition_name = "storage";
        const char *_base_path;
        wl_handle_t _wl_handle = WL_INVALID_HANDLE; 

    public:

        FAT_Storage(std::string file_name, std::string base_path, std::string TAG_FOR_LOG);
        ~FAT_Storage();
        void FAT_init();
        void print_file_content();
        void append_to_file(const char *data, size_t len);
        const char *TAG;
        FILE *F_UART;
        const char *_DATA_FILE_PATH;
};
