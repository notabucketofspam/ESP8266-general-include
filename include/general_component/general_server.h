#ifndef GENERAL_SERVER_H
#define GENERAL_SERVER_H

#include "general_include.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Set server config to default values */
#define SERVER_DEFAULT_CONFIG(x) {        \
  .httpd_config = HTTPD_DEFAULT_CONFIG(), \
  .httpd_handle = x,                      \
}

static const char *SERVER_TAG = "general_server";
/* index.html of HTTPD server  */
static FILE *f_index_html;
/* HTTPD server settings */
typedef struct {
  httpd_config_t httpd_config;
  httpd_handle_t httpd_handle;
} server_config_t;

/* Initialize HTTPD server */
esp_err_t setup_server(server_config_t server_config);
/* URI handler for index.html request from client */
static esp_err_t index_html_get_handler(httpd_req_t *req);
/* URI handler for base path request from client */
static esp_err_t base_path_get_handler(httpd_req_t *req);

#ifdef __cplusplus
}
#endif

#endif //GENERAL_SERVER_H