#ifndef GENERAL_NETWORK_H
#define GENERAL_NETWORK_H

#include "general_include.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RECEIVE_IP_BIT BIT(0)
/* Set network config to default values */
#define NETWORK_DEFAULT_CONFIG() {    \
  .sta = {                            \
    .ssid = CONFIG_WIFI_SSID,         \
    .password = CONFIG_WIFI_PASSWORD, \
  }                                   \
}

static const char *NETWORK_TAG = "general_network";
/* Event handler for WiFi connection */
static EventGroupHandle_t s_connection_event_group;
/* Nnetwork connection settings */
typedef wifi_config_t network_config_t;

/* Initialize WiFi network */
esp_err_t setup_network(network_config_t network_config);
/* Event handler for IPv4 address receive */
static void connection_receive_ip(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

#ifdef __cplusplus
}
#endif

#endif // GENERAL_NETWORK_H