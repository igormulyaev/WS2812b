#ifndef M_HTTP_SERVER_H
#define M_HTTP_SERVER_H

#include <string>
#include "esp_http_server.h"

#define SCRATCH_BUFSIZE (10240)

class HttpServer 
{
  public:
    HttpServer();
    ~HttpServer();

    esp_err_t startServer (const char* inBasePath);

  private:
    // URI handlers
    static esp_err_t systemInfoGetHandler (httpd_req_t *req);
    static esp_err_t commonGetHandler (httpd_req_t *req);
    
    // URI Executors
    esp_err_t commonGetExec (httpd_req_t *req);

    httpd_handle_t server;
    std::string basePath;

    char buf [SCRATCH_BUFSIZE];

    esp_err_t setContentTypeFromFileName (httpd_req_t *req, const std::string &filePath);

    HttpServer(const HttpServer &) = delete;
    HttpServer & operator=(const HttpServer &) = delete;
};
#endif