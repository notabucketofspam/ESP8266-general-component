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
  #define PIN_BIT_MASK (BIT(0) | BIT(1) | BIT(2) | BIT(3))
#else
  #define PIN_BIT_MASK (0x1FFFF)
#endif
/* Set all pins to output */
#define CONTROL_DEFAULT_CONFIG() {          \
  .keep_peripheral = CONTROL_UART_0,        \
  .auto_load_persistent_pin_state = true,   \
  .pin_mask_output = GPIO_Pin_All,          \
  .pin_mask_input = 0x0000,                 \
}

static const char *CONTROL_TAG = "general_control";
/* Available pins on selected board */
char s_pin_bit_mask[GPIO_PIN_COUNT] = { 0 };
/* Configured mode of pins (input / output) */
char s_pin_mode[GPIO_PIN_COUNT] = { 0 };
/* Persistent map of pin states */
static FILE *f_gpio_state;
/* Pin states stored in memory */
char s_gpio_state_mem[GPIO_PIN_COUNT] = { 0 };
/* Control state of pins */
typedef enum {
  CONTROL_UART_0  = (BIT(1) | BIT(3)),
  CONTROL_UART_1  = (BIT(2)),
  CONTROL_I2C     = (BIT(4) | BIT(5)),
  CONTROL_SPI     = (BIT(12) | BIT(13) | BIT(14) | BIT(15)),
} control_peripheral_t;
typedef struct {
  unsigned long long keep_peripheral;   // Pin mask for which peripherals to keep
  bool auto_load_persistent_pin_state;  // Use f_gpio_state file at boot?
  unsigned long long pin_mask_output;   // GPIO pins set to output
  unsigned long long pin_mask_input;    // GPIO pins set to input
} control_config_t;

/* Initialize GPIO control */
esp_err_t setup_control(control_config_t control_config);
/* Set pin states based on persistent file */
esp_err_t load_persistent_gpio_state(FILE *file_src);

#ifdef __cplusplus
}
#endif

#endif // GENERAL_CONTROL_H