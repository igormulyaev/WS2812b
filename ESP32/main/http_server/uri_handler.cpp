#include "esp_http_server.h"

#include "http_server/uri_handler.h"

// -----------------------------------------------------
void UriHandler :: registerUri (const char* inUri, bool isGet, bool isPost)
{
  httpd_uri_t uriConfig = {
    .uri = inUri,
    .user_ctx = static_cast <void*> (this)
  };

  if (isGet) {
    uriConfig.method = HTTP_GET;
    uriConfig.handler = getUriHandler;

    ESP_ERROR_CHECK (httpd_register_uri_handler (httpServer -> server, &uriConfig));
  }

  if (isPost) {
    uriConfig.method = HTTP_POST;
    uriConfig.handler = postUriHandler;

    ESP_ERROR_CHECK (httpd_register_uri_handler (httpServer -> server, &uriConfig));
  }
}

// -----------------------------------------------------
esp_err_t UriHandler :: getUriHandler (httpd_req_t* req)
{
  UriHandler* uriHandler = static_cast <UriHandler*> (req -> user_ctx);
  return uriHandler -> uriExecute (false, req);
}

// -----------------------------------------------------
esp_err_t UriHandler :: postUriHandler (httpd_req_t* req)
{
  UriHandler* uriHandler = static_cast <UriHandler*> (req -> user_ctx);
  return uriHandler -> uriExecute (true, req);
}
