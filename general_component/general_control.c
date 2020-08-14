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
  ESP_ERROR_CHECK(gpio_config(&control_output));
  ESP_LOGI(CONTROL_TAG, "C0");
  vTaskDelay(1000 / portTICK_RATE_MS);
  gpio_config_t control_input = {
    .pin_bit_mask = (PIN_BIT_MASK & control_config.pin_mask_input),
    .mode = GPIO_MODE_INPUT,
  };
  ESP_ERROR_CHECK(gpio_config(&control_input));
  ESP_LOGI(CONTROL_TAG, "C1");
  vTaskDelay(1000 / portTICK_RATE_MS);
  memset(s_pin_mode, 0x30, sizeof(s_pin_mode));
  memset(s_pin_bit_mask, 0x30, sizeof(s_pin_bit_mask));
  uint8_t config_index;
  for (config_index = 0; config_index < GPIO_PIN_COUNT; ++config_index) {
    if (!(PIN_BIT_MASK & BIT(config_index)))
      continue;
    s_pin_mode[config_index] = (BIT(config_index) & control_config.pin_mask_input) ? '1' : 
      (BIT(config_index) & control_config.pin_mask_output) ? '2' : '0';
    s_pin_bit_mask[config_index] = (PIN_BIT_MASK & BIT(config_index)) ? '1' : '0';
  }
  if (control_config.auto_load_persistent_pin_state)
    ESP_ERROR_CHECK(load_persistent_gpio_state());
  ESP_LOGI(CONTROL_TAG, "Control OK");
  return ESP_OK;
}

esp_err_t load_persistent_gpio_state(void) {
  bool pin_state;
  uint8_t state_index;
  for (state_index = 0; state_index < GPIO_PIN_COUNT; ++state_index) {
    pin_state = (fgetc(f_gpio_state) == '1');
    s_gpio_state_mem[state_index] = pin_state;
    if (s_pin_mode[state_index] == '2')
      ESP_ERROR_CHECK(gpio_set_level(state_index, pin_state));
  }
  rewind(f_gpio_state);
  return ESP_OK;
}

#ifdef __cplusplus
}
#endif
