#ifndef DEFAULT_HANDLER_H
#define DEFAULT_HANDLER_H

#include "uri_handler.h"
#include <string>

class DefaultHandler: public UriHandler
{
  public:
    DefaultHandler (HttpServer* inHttpServer);
    virtual ~DefaultHandler() {};

  private:
    virtual esp_err_t uriExecute (bool isPost, httpd_req_t* req);

    static esp_err_t setContentTypeFromFileName (httpd_req_t* req, const std::string &filePath);

    static const char* const uri;
    static const char* const tag;

    DefaultHandler (const DefaultHandler &) = delete;
    DefaultHandler & operator=(const DefaultHandler &) = delete;
};

#endif