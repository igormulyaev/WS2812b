#ifndef SYSINFO_HANDLER_H
#define SYSINFO_HANDLER_H

#include "uri_handler.h"

class SysinfoHandler: public UriHandler
{
  public:
    SysinfoHandler (HttpServer* inHttpServer);
    virtual ~SysinfoHandler() {};

  private:
    virtual esp_err_t uriExecute (bool isPost, httpd_req_t* req);

    static const char* const uri;
    static const char* const tag;

    SysinfoHandler (const SysinfoHandler &) = delete;
    SysinfoHandler & operator=(const SysinfoHandler &) = delete;
};

#endif