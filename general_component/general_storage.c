#include "general_storage.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t setup_storage(storage_config_t storage_config) {
  ESP_LOGI(STORAGE_TAG, "Setup storage");
	ESP_ERROR_CHECK(esp_vfs_spiffs_register(&storage_config));
  #if CONFIG_LOG_DEFAULT_LEVEL > 3
    size_t total_bytes, used_bytes;
    ESP_ERROR_CHECK(esp_spiffs_info(NULL, &total_bytes, &used_bytes));
    ESP_LOGD(STORAGE_TAG,"SPIFFS: total bytes: %d used bytes: %d", total_bytes, used_bytes);
  #endif
  ESP_LOGI(STORAGE_TAG, "Storage OK");
  return ESP_OK;
}

esp_err_t storage_access(FILE *file_src, const char *file_path, storage_access_mode_t access_mode) {
  if (file_path == NULL) return ESP_FAIL;
  char s_access_mode[2] = { access_mode, 0 };
  switch (access_mode) {
    case STORAGE_CLOSE:
      fclose(file_src);
      break;
    case STORAGE_SAVE:
      fflush(file_src);
      break;
    case STORAGE_READ_WRITE:
      file_src = fopen(file_path, "r+");
      break;
    default:
      file_src = fopen(file_path, s_access_mode);
      break;
  }
  return ESP_OK;
}

#ifdef __cplusplus
}
#endif