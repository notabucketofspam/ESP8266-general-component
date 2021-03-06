#include "general_control.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t setup_control(control_config_t control_config) {
  ESP_LOGI(CONTROL_TAG, "Setup control");
  gpio_config_t control_output = {
    .pin_bit_mask = (PIN_BIT_MASK & control_config.pin_mask_output),
    .mode = GPIO_MODE_OUTPUT,
  };
  gpio_config_t control_input = {
    .pin_bit_mask = (PIN_BIT_MASK & control_config.pin_mask_input),
    .mode = GPIO_MODE_INPUT,
  };
  control_output.pin_bit_mask &= ~(control_config.keep_peripheral);
  control_input.pin_bit_mask &= ~(control_config.keep_peripheral);
  ESP_LOGW(CONTROL_TAG, "pin bit mask out: %x", control_output.pin_bit_mask);
  ESP_LOGW(CONTROL_TAG, "pin bit mask in: %x", control_input.pin_bit_mask);
  if (control_output.pin_bit_mask)
    ESP_ERROR_CHECK(gpio_config(&control_output));
  if (control_input.pin_bit_mask)
    ESP_ERROR_CHECK(gpio_config(&control_input));
  memset(s_pin_mode, 0x30, sizeof(s_pin_mode));
  memset(s_pin_bit_mask, 0x30, sizeof(s_pin_bit_mask));
  uint8_t config_index;
  for (config_index = 0; config_index < GPIO_PIN_COUNT; ++config_index) {
    if (!(PIN_BIT_MASK & BIT(config_index)))
      continue;
    s_pin_bit_mask[config_index] = ((BIT(config_index) & control_input.pin_bit_mask) ||
      (BIT(config_index) & control_output.pin_bit_mask)) ? '1' : '0';
    s_pin_mode[config_index] = (BIT(config_index) & control_input.pin_bit_mask) ? '1' : 
      (BIT(config_index) & control_output.pin_bit_mask) ? '2' : '0';
  }
  char buf[GPIO_PIN_COUNT + 1] = { 0 };
  memcpy(buf, s_pin_bit_mask, sizeof(s_pin_bit_mask));
  ESP_LOGW(CONTROL_TAG, "mask %s", buf);
  memcpy(buf, s_pin_mode, sizeof(s_pin_mode));
  ESP_LOGW(CONTROL_TAG, "mode %s", buf);
  ESP_LOGI(CONTROL_TAG, "Control OK");
  return ESP_OK;
}

esp_err_t load_persistent_gpio_state(FILE *file_src) {
  bool pin_state = 0;
  uint8_t state_index;
  for (state_index = 0; state_index < GPIO_PIN_COUNT; ++state_index) {
    pin_state = (fgetc(file_src) == '1');
    s_gpio_state_mem[state_index] = pin_state;
    if (s_pin_mode[state_index] == '2')
      ESP_ERROR_CHECK(gpio_set_level(state_index, pin_state));
  }
  rewind(file_src);
  return ESP_OK;
}

#ifdef __cplusplus
}
#endif
