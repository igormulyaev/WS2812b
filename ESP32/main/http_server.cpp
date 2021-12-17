#include "http_server.h"

// -----------------------------------------------------
CHttpServer :: CHttpServer () : 
  server (NULL) {
}

// -----------------------------------------------------
CHttpServer :: ~CHttpServer () {
  if (server != NULL) {
    ESP_ERROR_CHECK (httpd_stop (server));
    server = NULL;
  }
}

