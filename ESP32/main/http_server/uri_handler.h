#ifndef URI_HANDLER_H
#define URI_HANDLER_H

#include "esp_http_server.h"

class HttpServer;

class UriHandler 
{
  public:
    UriHandler (HttpServer* inHttpServer, const char* uri, bool isGet, bool isPost);
    virtual ~UriHandler () {};

  protected:
    char* getBuf ();

  private:
    virtual esp_err_t uriExecute (bool isPost, httpd_req_t* req) = 0;

    // URI handlers
    static esp_err_t getUriHandler (httpd_req_t* req);
    static esp_err_t postUriHandler (httpd_req_t* req);

    HttpServer* httpServer;

    UriHandler (const UriHandler &) = delete;
    UriHandler & operator=(const UriHandler &) = delete;
};
#endif