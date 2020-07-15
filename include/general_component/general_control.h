#ifndef GENERAL_CONTROL_H
#define GENERAL_CONTROL_H

#include "general_include.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Available pins for specific boards */
#if defined(CONFIG_ESP_BOARD_NODEMCU)
  #define PIN_BIT_MASK (BIT(0) | BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5)  \
    | BIT(9) | BIT(10) | BIT(12) | BIT(13) | BIT(14) | BIT(15) | BIT(16))
#elif defined(CONFIG_ESP_BOARD_WEMOS_D1_MINI)
  #define PIN_BIT_MASK (BIT(0) | BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5)  \
    | BIT(12) | BIT(13) | BIT(14) | BIT(15) | BIT(16))
#elif defined(CONFIG_ESP_BOARD_ESP_01S)
  #define PIN_BIT_MASK (BIT(1) | BIT(3))
#else
  #define PIN_BIT_MASK (0x1FFFF)
#endif
/* Set specific pin to output */
#define CONTROL_PIN_DEFAULT_CONFIG(x) { \
  .pin_bit_mask = (BIT(x)),             \
  .mode = GPIO_MODE_OUTPUT,             \
}
/* Set all pins to output */
#define CONTROL_DEFAULT_CONFIG() {          \
  .auto_load_persistent_pin_state = false,  \
  .control_list = {                         \
    CONTROL_PIN_DEFAULT_CONFIG(0),          \
    CONTROL_PIN_DEFAULT_CONFIG(1),          \
    CONTROL_PIN_DEFAULT_CONFIG(2),          \
    CONTROL_PIN_DEFAULT_CONFIG(3),          \
    CONTROL_PIN_DEFAULT_CONFIG(4),          \
    CONTROL_PIN_DEFAULT_CONFIG(5),          \
    CONTROL_PIN_DEFAULT_CONFIG(6),          \
    CONTROL_PIN_DEFAULT_CONFIG(7),          \
    CONTROL_PIN_DEFAULT_CONFIG(8),          \
    CONTROL_PIN_DEFAULT_CONFIG(9),          \
    CONTROL_PIN_DEFAULT_CONFIG(10),         \
    CONTROL_PIN_DEFAULT_CONFIG(11),         \
    CONTROL_PIN_DEFAULT_CONFIG(12),         \
    CONTROL_PIN_DEFAULT_CONFIG(13),         \
    CONTROL_PIN_DEFAULT_CONFIG(14),         \
    CONTROL_PIN_DEFAULT_CONFIG(15),         \
    CONTROL_PIN_DEFAULT_CONFIG(16),         \
  },                                        \
}
/* Reverse direction of array reading */
#define GPIO_RTL(x) (GPIO_PIN_COUNT - 1 - x)

static const char *TAG = "general_control";
/* Available pins on selected board */
static uint8_t s_pin_bit_mask[GPIO_PIN_COUNT];
/* Configured mode of pins (input / output) */
static uint8_t s_pin_mode[GPIO_PIN_COUNT];
/* Persistent map of pin states */
static FILE *s_gpio_state;
/* Pin states stored in memory */
static uint8_t s_gpio_state_mem[GPIO_PIN_COUNT];
/* Control state of pins */
typedef struct {
  bool auto_load_persistent_pin_state;        // Use s_gpio_state file at boot?
  gpio_config_t control_list[GPIO_PIN_COUNT]; // Collection of GPIO configs, one for each pin
} control_config_t;

/* Initialize GPIO control */
esp_err_t setup_control(const control_config_t *control_config);
/* Set pin states based on persistent file */
esp_err_t load_persistent_gpio_state(void);

#ifdef __cplusplus
}
#endif

#endif // GENERAL_CONTROL_H