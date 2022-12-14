#include "sysinfo_handler.h"
#include "esp_log.h"
#include "esp_chip_info.h"

// ########################################################################
// ### Initialization, registering URI
// ########################################################################
SysinfoHandler :: SysinfoHandler (HttpServer* inHttpServer)
: UriHandler (inHttpServer, uri, true, false)
{}

// ########################################################################
// ### GET handler
// ########################################################################
esp_err_t SysinfoHandler :: uriExecute (bool isPost, httpd_req_t* req)
{
  ESP_LOGI (tag, "Get version");

  httpd_resp_set_type (req, "application/json");

  esp_chip_info_t chipInfo;
  esp_chip_info (&chipInfo);

  char* buf = getBuf ();

  sprintf (buf, "{version: \"%s\", cores: %d}", IDF_VER, chipInfo.cores);
  return httpd_resp_sendstr(req, buf);
}

const char* const SysinfoHandler :: uri = "/api/v1/system/info";
const char* const SysinfoHandler :: tag = "sysinfo";
