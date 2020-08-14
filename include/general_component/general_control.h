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
  .keep_uart = (BIT(0) & BIT(1)),           \
  .auto_load_persistent_pin_state = true,   \
  .pin_mask_output = GPIO_Pin_All,          \
  .pin_mask_input = 0x0000,                 \
}

static const char *CONTROL_TAG = "general_control";
/* Available pins on selected board */
static char s_pin_bit_mask[GPIO_PIN_COUNT];
/* Configured mode of pins (input / output) */
static char s_pin_mode[GPIO_PIN_COUNT];
/* Persistent map of pin states */
static FILE *f_gpio_state;
/* Pin states stored in memory */
static char s_gpio_state_mem[GPIO_PIN_COUNT];
/* Control state of pins */
typedef struct {
  bool keep_uart_1;                     // Keep UART1 TX for debugging
  unsigned char keep_uart;              // Pin mask for which UART ports to keep
  bool auto_load_persistent_pin_state;  // Use f_gpio_state file at boot?
  unsigned long long pin_mask_output;   // GPIO pins set to output
  unsigned long long pin_mask_input;    // GPIO pins set to input
} control_config_t;

/* Initialize GPIO control */
esp_err_t setup_control(control_config_t control_config);
/* Set pin states based on persistent file */
esp_err_t load_persistent_gpio_state(void);

#ifdef __cplusplus
}
#endif

#endif // GENERAL_CONTROL_H