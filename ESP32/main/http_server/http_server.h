#ifndef M_HTTP_SERVER_H
#define M_HTTP_SERVER_H

#include <string>
#include "esp_http_server.h"

#define SCRATCH_BUFSIZE (10240)

class HttpServer 
{
  public:
    HttpServer(const char* inBasePath);
    ~HttpServer();

  private:
    void registerUri (const char* uri, httpd_method_t method, esp_err_t (*handler)(httpd_req_t *r));

    // URI handlers
    static esp_err_t systemInfoGetUriHandler (httpd_req_t* req);
    static esp_err_t commonGetUriHandler (httpd_req_t* req);

    static esp_err_t testLedGetUriHandler (httpd_req_t* req);
    static esp_err_t testLedPostUriHandler (httpd_req_t* req);
    esp_err_t testLedExecute (bool isPost, httpd_req_t* req);

    static esp_err_t setContentTypeFromFileName (httpd_req_t* req, const std::string &filePath);
    esp_err_t readPostData (httpd_req_t* req);


    httpd_handle_t server;
    std::string basePath;

    char buf [SCRATCH_BUFSIZE];

    static const char* const TAG;

    HttpServer(const HttpServer &) = delete;
    HttpServer & operator=(const HttpServer &) = delete;
};
#endif