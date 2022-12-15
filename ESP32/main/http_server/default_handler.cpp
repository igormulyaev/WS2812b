#include "default_handler.h"
#include "esp_log.h"
#include "net_base.h"
#include <fcntl.h>
#include "http_server.h"


// ########################################################################
// ### Initialization, registering URI
// ########################################################################
DefaultHandler :: DefaultHandler (HttpServer* inHttpServer)
: UriHandler (inHttpServer, uri, true, false)
{}

// ########################################################################
// ### GET handler
// ########################################################################
esp_err_t DefaultHandler :: uriExecute (bool isPost, httpd_req_t* req)
{
  ESP_LOGI (tag, "Get default: %s", req -> uri);

  std::string filePath = WEB_MOUNT_POINT;

  filePath.append (req -> uri);

  if (filePath [filePath.length() - 1] == '/') {
    filePath.append ("index.html");
  }

  int fd = open (filePath.c_str(), O_RDONLY, 0);

  if (fd == -1) {
    ESP_LOGE(tag, "Failed to open file : %s", filePath.c_str());
    // Respond with 500 Internal Server Error
    ESP_ERROR_CHECK (httpd_resp_send_err (req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to open file"));
    return ESP_FAIL;
  }

  ESP_ERROR_CHECK (setContentTypeFromFileName (req, filePath));

  char *chunk = getBuf ();
  ssize_t read_bytes;
  do {
    // Read file in chunks into the scratch buffer
    read_bytes = read(fd, chunk, SCRATCH_BUFSIZE);

    if (read_bytes == -1) {
      ESP_LOGE(tag, "Failed to read file: %s", filePath.c_str());
    } 
    else if (read_bytes > 0) {
      // Send the buffer contents as HTTP response chunk
      if (httpd_resp_send_chunk (req, chunk, read_bytes) != ESP_OK) {
        close (fd);
        ESP_LOGE(tag, "File sending failed!");
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

  ESP_LOGI (tag, "File sending complete");
  // Respond with an empty chunk to signal HTTP response completion
  return httpd_resp_send_chunk(req, NULL, 0);
}

// ########################################################################
// ### Set HTTP response content type according to file extension
// ########################################################################
esp_err_t DefaultHandler :: setContentTypeFromFileName (httpd_req_t* req, const std::string &filePath)
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
  ESP_LOGI (tag, "MIME type: %s", type);

  return httpd_resp_set_type (req, type);
}

const char* const DefaultHandler :: uri = "/*";
const char* const DefaultHandler :: tag = "defURI";
