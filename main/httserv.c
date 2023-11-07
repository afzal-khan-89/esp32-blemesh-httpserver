
/*  WiFi softAP Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "esp_http_server.h"



extern void k_example_ble_mesh_send_gen_onoff_set(void) ;


static const char *TAG = "http softAP";



static esp_err_t button_handler(httpd_req_t *req)
{
 
    k_example_ble_mesh_send_gen_onoff_set() ;

}

static esp_err_t get_handler(httpd_req_t *req)
{
    char *response_message = "<!DOCTYPE html>\
<html>\
<head>\
<style>\
.button {\
  border: none;\
  color: white;\
  padding: 15px 32px;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  font-size: 16px;\
  margin: 4px 2px;\
  cursor: pointer;\
}\
\
.button1 {background-color: #4CAF50;} \
.button2 {background-color: #008CBA;} \
</style>\
</head>\
<body>\
\
<h1>Teton Electronics Ltd.</h1>\
<p>Ble Mesh Switching </p>\
\
<button class=\"button button1\" onclick=\"window.location.href='https://www.w3docs.com';\" value=\"w3docs\">On</button>\
<button class=\"button button2\" onclick=\"window.location.href='https://www.w3docs.com';\" value=\"w3docs\" >Off</button>\
\
</body>\
</html>\
";
    httpd_resp_send(req, response_message, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static void create_http_server(void *arg)
{
    httpd_config_t server_config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server_handle = NULL;
    httpd_start(&server_handle, &server_config);

    httpd_uri_t uri_get = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = get_handler,
        .user_ctx = NULL};
    httpd_register_uri_handler(server_handle, &uri_get);
    
    while (1)
    {
        vTaskDelay(100);
    }
    
}
void server_initiation()
{
    BaseType_t ret = xTaskCreatePinnedToCore(create_http_server, "http_server_task", 4096, NULL, 1, NULL, 0);
    if (ret != pdPASS) {
        ESP_LOGE(TAG, "create task %s failed", "http_server_task");
    }
}

