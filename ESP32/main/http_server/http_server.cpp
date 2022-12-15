#include "http_server.h"
#include "esp_log.h"
#include "sysinfo_handler.h"
#include "default_handler.h"

const char* const HttpServer :: TAG = "http_server";

// -----------------------------------------------------
HttpServer :: HttpServer ()
: server (NULL)
{
  // Starting server
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.uri_match_fn = httpd_uri_match_wildcard;

  ESP_LOGI(TAG, "Starting HTTP Server");
  ESP_ERROR_CHECK (httpd_start (&server, &config));
  ESP_LOGI(TAG, "HTTP Server started");

  // Add URI handlers
  sysinfoHandler = new SysinfoHandler (this);
  registerUri ("/api/test_led", HTTP_GET, testLedGetUriHandler);
  registerUri ("/api/test_led", HTTP_POST, testLedPostUriHandler);
  registerUri ("/api/simple_effects", HTTP_GET, simpleEffectsGetUriHandler);
  registerUri ("/api/simple_effects", HTTP_POST, simpleEffectsPostUriHandler);

  // Other web server files 
  defaultHandler = new DefaultHandler (this);
}

// -----------------------------------------------------
HttpServer :: ~HttpServer () 
{
  delete defaultHandler;
  delete sysinfoHandler;

  if (server) {
    ESP_ERROR_CHECK (httpd_stop (server));
    server = NULL;
  }
}

// -----------------------------------------------------
void HttpServer :: registerUri (const char* p_uri, 
                                httpd_method_t p_method, 
                                esp_err_t (*p_handler)(httpd_req_t *r))
{
  httpd_uri_t uriConfig = {
    .uri = p_uri,
    .method = p_method,
    .handler = p_handler,
    .user_ctx = static_cast <void*> (this)
  };
  ESP_ERROR_CHECK (httpd_register_uri_handler (server, &uriConfig));
}

// -----------------------------------------------------
// Read POST data to buf
esp_err_t HttpServer :: readPostData (httpd_req_t* req)
{
  int total_len = req -> content_len;
  int cur_len = 0;
  int received = 0;

  if (total_len >= SCRATCH_BUFSIZE) {
    httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "content too long");
    return ESP_FAIL;
  }

  while (cur_len < total_len) {
    received = httpd_req_recv (req, buf + cur_len, total_len);
    if (received <= 0) {
      httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to post control value");
      return ESP_FAIL;
    }
    cur_len += received;
  }

  buf[total_len] = '\0';
  return ESP_OK;
}