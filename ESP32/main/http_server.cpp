#include "http_server.h"
#include "esp_log.h"
#include "cJSON.h"
#include <fcntl.h>

static const char* TAG = "http_server";

// -----------------------------------------------------
HttpServer :: HttpServer () : 
  server (NULL)
{
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
esp_err_t HttpServer :: startServer (const char* inBasePath) 
{
  if (server) {
    return ESP_FAIL;
    ESP_LOGE (TAG, "Server always started");
  }

  basePath = inBasePath;
  
  // Starting server
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.uri_match_fn = httpd_uri_match_wildcard;

  ESP_LOGI(TAG, "Starting HTTP Server");
  ESP_ERROR_CHECK (httpd_start (&server, &config));
  ESP_LOGI(TAG, "HTTP Server started");

  // Add URI handlers
  // System info
  httpd_uri_t systemInfoGetUri = {
    .uri = "/api/v1/system/info",
    .method = HTTP_GET,
    .handler = HttpServer :: systemInfoGetHandler,
    .user_ctx = static_cast <void*> (this)
  };
  ESP_ERROR_CHECK (httpd_register_uri_handler (server, &systemInfoGetUri));

  // Other web server files 
  httpd_uri_t commonGetUri = {
      .uri = "/*",
      .method = HTTP_GET,
      .handler = commonGetHandler,
      .user_ctx = static_cast <void*> (this)
  };
  ESP_ERROR_CHECK (httpd_register_uri_handler(server, &commonGetUri));

  return ESP_OK;
}

// -----------------------------------------------------
esp_err_t HttpServer :: systemInfoGetHandler (httpd_req_t *req)
{
  ESP_LOGI (TAG, "Get version");
  
  httpd_resp_set_type (req, "application/json");

  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  cJSON *root = cJSON_CreateObject();
  cJSON_AddStringToObject(root, "version", IDF_VER);
  cJSON_AddNumberToObject(root, "cores", chip_info.cores);

  const char *sys_info = cJSON_Print(root);
  httpd_resp_sendstr(req, sys_info);
  free((void *)sys_info);

  cJSON_Delete(root);
  return ESP_OK;
}

// -----------------------------------------------------
esp_err_t HttpServer :: commonGetHandler (httpd_req_t *req)
{
  HttpServer* srv = static_cast <HttpServer*> (req -> user_ctx);
  return srv -> commonGetExec (req);
}

// -----------------------------------------------------
esp_err_t HttpServer :: commonGetExec (httpd_req_t *req)
{
  ESP_LOGI (TAG, "Get common: %s", req -> uri);

  std::string filePath = basePath;

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

  char *chunk = buf;
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
