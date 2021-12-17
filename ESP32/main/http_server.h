#ifndef M_HTTP_SERVER_H
#define M_HTTP_SERVER_H

#include "esp_http_server.h"

class CHttpServer {
  private:
    CHttpServer(const CHttpServer &) = delete;
    CHttpServer & operator=(const CHttpServer &) = delete;

    httpd_handle_t server;

  public:
    CHttpServer();
    ~CHttpServer();

};
#endif