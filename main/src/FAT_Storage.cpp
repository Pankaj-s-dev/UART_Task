#include "FAT_Storage.h"

#define MAX_FILE_OPEN 5
#define ALLOCATION_UNIT_SIZE 8096
std::string TEMP_DATA_FILE;

FAT_Storage::FAT_Storage(std::string file_name, std::string base_path, std::string TAG_FOR_LOG){
    _base_path = base_path.c_str();
    TAG = TAG_FOR_LOG.c_str();
    _file_name = file_name.c_str();
    TEMP_DATA_FILE = (base_path + "/" + file_name);
    _DATA_FILE_PATH = TEMP_DATA_FILE.c_str();
    ESP_LOGI(TAG, "FAT_Storage object created");
    FAT_init();
}

FAT_Storage::~FAT_Storage() {
    esp_vfs_fat_spiflash_unmount(_base_path, _wl_handle);
    ESP_LOGI(TAG, "FAT_Storage object destroyed");
}
//function to initialize the FAT file system
void FAT_Storage::FAT_init() {
    esp_vfs_fat_mount_config_t FAT_mount_config = {
        .format_if_mount_failed = true,
        .max_files = MAX_FILE_OPEN,
        .allocation_unit_size = ALLOCATION_UNIT_SIZE
    }; 
    esp_err_t ret = esp_vfs_fat_spiflash_mount_rw_wl(_base_path, _Partition_name, &FAT_mount_config, &_wl_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to mount filesystaem: %s", esp_err_to_name(ret));
        return;
    }

    ESP_LOGI(TAG, "Filesystem mounted.");
    F_UART = fopen(_DATA_FILE_PATH, "w");
    if (F_UART == NULL) {
        ESP_LOGE(TAG, "Can not open file for writing %s", _DATA_FILE_PATH);
        return;
    }
    ESP_LOGI(TAG, "Filesystem Created OK");
    fclose(F_UART); 
}

// function to print the content of the file
void FAT_Storage::print_file_content() {
    F_UART = fopen(_DATA_FILE_PATH, "r");  
    if (F_UART == NULL) {
        ESP_LOGE(TAG, "could not open the file for reading");
        return;
    }
    struct stat txt_f_info;
    if (fstat(fileno(F_UART), &txt_f_info) != 0) {
        ESP_LOGE(TAG, "Failed to readthe txt file size");
        fclose(F_UART);
        return;
    }

    size_t txt_f_size = txt_f_info.st_size;

    char *line = new char[txt_f_size + 1];

    fgets(line, (txt_f_size + 1), F_UART);  
    ESP_LOGI(TAG, "Below are the Content :\n");
    printf("%s\n",line); 

    delete[] line;

    fclose(F_UART); 

    vTaskDelay(pdMS_TO_TICKS(100));

    F_UART = fopen(_DATA_FILE_PATH, "w");

    if (F_UART != NULL) {
        ESP_LOGI(TAG, "File cleared");
    }


    fclose(F_UART);  
}

// function to append data to the file
void FAT_Storage::append_to_file(const char *data, size_t len) {
    F_UART = fopen(_DATA_FILE_PATH, "a"); 
    if (F_UART == NULL) {
        ESP_LOGE(TAG, "No file availabe %s", _DATA_FILE_PATH);
        return;
    }

    size_t written = fwrite(data, 1, len, F_UART); 
    if (written != len) {
        ESP_LOGE(TAG, "Failed to write the full data to the file");
    }
    ESP_LOGI(TAG, "Saved to File");
    fclose(F_UART);  
}