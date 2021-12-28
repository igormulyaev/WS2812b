#ifndef M_URI_HANDLER_H
#define M_URI_HANDLER_H

#include "esp_http_server.h"

#include "http_server/http_server.h"

class UriHandler 
{
  public:
    UriHandler (HttpServer* inHttpServer):
      httpServer (inHttpServer)
    {}
    virtual ~UriHandler() {};

    void registerUri (const char* uri, bool isGet, bool isPost);

  protected:
    char* getBuf() { return httpServer -> buf; }

  private:
    // URI handlers
    static esp_err_t getUriHandler (httpd_req_t* req);
    static esp_err_t postUriHandler (httpd_req_t* req);

    virtual esp_err_t uriExecute (bool isPost, httpd_req_t* req) = 0;

    HttpServer* httpServer;

    UriHandler (const UriHandler &) = delete;
    UriHandler & operator=(const UriHandler &) = delete;
};
#endif