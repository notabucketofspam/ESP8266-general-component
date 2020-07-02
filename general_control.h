#ifndef GENERAL_CONTROL_H
#define GENERAL_CONTROL_H

#include "general_include.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Set specific pin to output */
#define CONTROL_PIN_DEFAULT_CONFIG(x) { \
  .pin_bit_mask = GPIO_Pin_##x,         \
  .mode = GPIO_MODE_OUTPUT,             \
}
/* Set all pins to output */
#define CONTROL_DEFAULT_CONFIG() {      \
  .persistent_pin_state = false,        \
  .control_list = {                     \
    CONTROL_PIN_DEFAULT_CONFIG(0),      \
    CONTROL_PIN_DEFAULT_CONFIG(1),      \
    CONTROL_PIN_DEFAULT_CONFIG(2),      \
    CONTROL_PIN_DEFAULT_CONFIG(3),      \
    CONTROL_PIN_DEFAULT_CONFIG(4),      \
    CONTROL_PIN_DEFAULT_CONFIG(5),      \
    CONTROL_PIN_DEFAULT_CONFIG(6),      \
    CONTROL_PIN_DEFAULT_CONFIG(7),      \
    CONTROL_PIN_DEFAULT_CONFIG(8),      \
    CONTROL_PIN_DEFAULT_CONFIG(9),      \
    CONTROL_PIN_DEFAULT_CONFIG(10),     \
    CONTROL_PIN_DEFAULT_CONFIG(11),     \
    CONTROL_PIN_DEFAULT_CONFIG(12),     \
    CONTROL_PIN_DEFAULT_CONFIG(13),     \
    CONTROL_PIN_DEFAULT_CONFIG(14),     \
    CONTROL_PIN_DEFAULT_CONFIG(15),     \
    CONTROL_PIN_DEFAULT_CONFIG(16),     \
  },                                    \
}

static const char *TAG = "general_control";
/* Persistent map of pin states */
static FILE *s_gpio_state;
/* Pin states stored in memory */
static uint8_t s_gpio_state_mem[17];
/* Control state of specific pin */
typedef struct {
  bool persistent_pin_state;        // Use gpio_state file?
  gpio_config_t control_list[17];   // Collection of GPIO configs, one for each pin
} control_config_t;

/* Initialize GPIO control */
esp_err_t setup_control(const control_config_t *control_config);
/* Set pin states based on persistent file */
esp_err_t read_persistent_gpio_state(void);

#ifdef __cplusplus
}
#endif

#endif // GENERAL_CONTROL_H