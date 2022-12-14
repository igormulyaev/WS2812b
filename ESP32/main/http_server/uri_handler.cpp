#include "esp_http_server.h"

#include "uri_handler.h"
#include "http_server.h"

// ########################################################################
// ### Constructor, registers URI
// ########################################################################
UriHandler :: UriHandler (HttpServer* inHttpServer, const char* inUri, bool isGet, bool isPost)
: httpServer (inHttpServer)
{
  httpd_uri_t uriConfig = {
    .uri = inUri,
    .method = HTTP_GET,
    .handler = getUriHandler,
    .user_ctx = static_cast <void*> (this),
  };

  if (isGet) {
    ESP_ERROR_CHECK (httpd_register_uri_handler (httpServer -> server, &uriConfig));
  }

  if (isPost) {
    uriConfig.method = HTTP_POST;
    uriConfig.handler = postUriHandler;

    ESP_ERROR_CHECK (httpd_register_uri_handler (httpServer -> server, &uriConfig));
  }
}

// ########################################################################
// ### GET handler
// ########################################################################
esp_err_t UriHandler :: getUriHandler (httpd_req_t* req)
{
  UriHandler* uriHandler = static_cast <UriHandler*> (req -> user_ctx);
  return uriHandler -> uriExecute (false, req);
}

// ########################################################################
// ### POST handler
// ########################################################################
esp_err_t UriHandler :: postUriHandler (httpd_req_t* req)
{
  UriHandler* uriHandler = static_cast <UriHandler*> (req -> user_ctx);
  return uriHandler -> uriExecute (true, req);
}

// ########################################################################
// ### Get server buffer
// ########################################################################
char* UriHandler :: getBuf ()
{ 
  return httpServer -> buf; 
}