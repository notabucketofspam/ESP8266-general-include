#include "general_control.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t setup_control(const control_config_t *control_config) {
  ESP_LOGI(TAG, "Setup control");
  uint8_t config_index;
  for (config_index = 0; config_index < GPIO_PIN_COUNT; ++config_index) {
    if (!(PIN_BIT_MASK & BIT(config_index)))
      continue;
    ESP_ERROR_CHECK(gpio_config(&control_config->control_list[config_index]));
    s_pin_mode[GPIO_RTL(config_index)] = 0x30 + control_config->control_list[config_index].mode;
    s_pin_bit_mask[GPIO_RTL(config_index)] = (PIN_BIT_MASK & BIT(config_index)) ? '1' : '0';
  }
  if (control_config->auto_load_persistent_pin_state)
    ESP_ERROR_CHECK(load_persistent_gpio_state());
  ESP_LOGI(TAG, "Control OK");
  return ESP_OK;
}

esp_err_t load_persistent_gpio_state(void) {
  bool pin_state;
  uint8_t state_index;
  for (state_index = 0; state_index < GPIO_PIN_COUNT; ++state_index) {
    pin_state = (fgetc(s_gpio_state) == '1');
    s_gpio_state_mem[state_index] = pin_state;
    if (s_pin_mode[state_index] == '2')
      ESP_ERROR_CHECK(gpio_set_level(GPIO_RTL(state_index), pin_state));
  }
  rewind(s_gpio_state);
  return ESP_OK;
}

#ifdef __cplusplus
}
#endif
