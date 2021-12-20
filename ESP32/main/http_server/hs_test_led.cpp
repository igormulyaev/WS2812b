#include "http_server.h"
#include "esp_log.h"
//#include "cJSON.h"
//#include <fcntl.h>

// -----------------------------------------------------
esp_err_t HttpServer :: testLedGetUriHandler (httpd_req_t *req)
{
  ESP_LOGI (TAG, "Get test_led");
  HttpServer* srv = static_cast <HttpServer*> (req -> user_ctx);
  return srv -> testLedExecute (true, req);
}

// -----------------------------------------------------
esp_err_t HttpServer :: testLedPostUriHandler (httpd_req_t *req)
{
  ESP_LOGI (TAG, "Post test_led");
  HttpServer* srv = static_cast <HttpServer*> (req -> user_ctx);
  return srv -> testLedExecute (false, req);
}

// -----------------------------------------------------
esp_err_t HttpServer :: testLedExecute (bool isPost, httpd_req_t *req)
{
  httpd_resp_set_type (req, "application/json");

  sprintf (buf, "{\"state\": %d}", 0);

  return httpd_resp_sendstr(req, buf);
}