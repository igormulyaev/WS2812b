#include "http_server.h"
#include "esp_log.h"
#include <fcntl.h>

const char* const HttpServer :: TAG = "http_server";

// -----------------------------------------------------
HttpServer :: HttpServer (const char* inBasePath) : 
  server (NULL), basePath (inBasePath)
{
  // Starting server
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.uri_match_fn = httpd_uri_match_wildcard;

  ESP_LOGI(TAG, "Starting HTTP Server");
  ESP_ERROR_CHECK (httpd_start (&server, &config));
  ESP_LOGI(TAG, "HTTP Server started");

  // Add URI handlers
  registerUri ("/api/v1/system/info", HTTP_GET, systemInfoGetUriHandler);
  registerUri ("/api/test_led", HTTP_GET, testLedGetUriHandler);
  registerUri ("/api/test_led", HTTP_POST, testLedPostUriHandler);

  // Other web server files 
  registerUri ("/*", HTTP_GET, commonGetUriHandler);
}

// -----------------------------------------------------
HttpServer :: ~HttpServer () 
{
  if (server) {
    ESP_ERROR_CHECK (httpd_stop (server));
    server = NULL;
  }
}

// -----------------------------------------------------
void HttpServer :: registerUri (const char* p_uri, 
                                     httpd_method_t p_method, 
                                     esp_err_t (*p_handler)(httpd_req_t *r))
{
  httpd_uri_t uriConfig = {
    .uri = p_uri,
    .method = p_method,
    .handler = p_handler,
    .user_ctx = static_cast <void*> (this)
  };
  ESP_ERROR_CHECK (httpd_register_uri_handler (server, &uriConfig));
}

// -----------------------------------------------------
esp_err_t HttpServer :: systemInfoGetUriHandler (httpd_req_t *req)
{
  ESP_LOGI (TAG, "Get version");

  HttpServer* srv = static_cast <HttpServer*> (req -> user_ctx);
  
  httpd_resp_set_type (req, "application/json");

  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  char *sys_info = srv -> buf;

  sprintf (sys_info, "{version: \"%s\", cores: %d}", IDF_VER, chip_info.cores);
  return httpd_resp_sendstr(req, sys_info);
}

// -----------------------------------------------------
esp_err_t HttpServer :: commonGetUriHandler (httpd_req_t *req)
{
  ESP_LOGI (TAG, "Get common: %s", req -> uri);

  HttpServer* srv = static_cast <HttpServer*> (req -> user_ctx);

  std::string filePath = srv -> basePath;

  filePath.append (req -> uri);

  if (filePath [filePath.length() - 1] == '/') {
    filePath.append ("index.html");
  }

  int fd = open (filePath.c_str(), O_RDONLY, 0);

  if (fd == -1) {
    ESP_LOGE(TAG, "Failed to open file : %s", filePath.c_str());
    // Respond with 500 Internal Server Error
    ESP_ERROR_CHECK (httpd_resp_send_err (req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to open file"));
    return ESP_FAIL;
  }

  ESP_ERROR_CHECK (setContentTypeFromFileName (req, filePath));

  char *chunk = srv -> buf;
  ssize_t read_bytes;
  do {
    // Read file in chunks into the scratch buffer
    read_bytes = read(fd, chunk, SCRATCH_BUFSIZE);

    if (read_bytes == -1) {
      ESP_LOGE(TAG, "Failed to read file: %s", filePath.c_str());
    } 
    else if (read_bytes > 0) {
      // Send the buffer contents as HTTP response chunk
      if (httpd_resp_send_chunk (req, chunk, read_bytes) != ESP_OK) {
        close (fd);
        ESP_LOGE(TAG, "File sending failed!");
        // Abort sending file
        httpd_resp_sendstr_chunk (req, NULL);
        // Respond with 500 Internal Server Error
        httpd_resp_send_err (req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to send file");
        return ESP_FAIL;
      }
    }
  } while (read_bytes > 0);
  // Close file after sending complete
  close (fd);

  ESP_LOGI (TAG, "File sending complete");
  // Respond with an empty chunk to signal HTTP response completion
  return httpd_resp_send_chunk(req, NULL, 0);
}

// -----------------------------------------------------
// Set HTTP response content type according to file extension
esp_err_t HttpServer :: setContentTypeFromFileName (httpd_req_t *req, const std::string &filePath)
{
  const char *type = "text/plain";

  if (strcasecmp(filePath.c_str() + (filePath.length() - 5), ".html") == 0) {
    type = "text/html";
  }
  else if (strcasecmp(filePath.c_str() + (filePath.length() - 4), ".jpg") == 0) {
    type = "image/jpeg";
  }
  else if (strcasecmp(filePath.c_str() + (filePath.length() - 4), ".ico") == 0) {
    type = "image/x-icon";
  }
  else if (strcasecmp(filePath.c_str() + (filePath.length() - 4), ".png") == 0) {
    type = "image/png";
  }
  else if (strcasecmp(filePath.c_str() + (filePath.length() - 3), ".js") == 0) {
    type = "application/javascript";
  }
  else if (strcasecmp(filePath.c_str() + (filePath.length() - 4), ".css") == 0) {
    type = "text/css";
  }
  ESP_LOGI (TAG, "MIME type: %s", type);

  return httpd_resp_set_type (req, type);
}
