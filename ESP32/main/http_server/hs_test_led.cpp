#include "http_server.h"
#include "esp_log.h"
#include "led_base.h"
#include "led_event_loop.h"
#include "effects/test_effect.h"

// -----------------------------------------------------
esp_err_t HttpServer :: testLedGetUriHandler (httpd_req_t* req)
{
  ESP_LOGI (TAG, "Get test_led");
  HttpServer* srv = static_cast <HttpServer*> (req -> user_ctx);
  return srv -> testLedExecute (false, req);
}

// -----------------------------------------------------
esp_err_t HttpServer :: testLedPostUriHandler (httpd_req_t* req)
{
  ESP_LOGI (TAG, "Post test_led");
  HttpServer* srv = static_cast <HttpServer*> (req -> user_ctx);
  return srv -> testLedExecute (true, req);
}

// -----------------------------------------------------
esp_err_t HttpServer :: testLedExecute (bool isPost, httpd_req_t* req)
{
  const LedEffect* curEffect = ledEventLoop -> getLedEffect();
  bool isTestEffectOn = curEffect && curEffect -> getName() == TestEffect :: name;

  if (isPost) {
    esp_err_t rc = readPostData (req);
    if ( rc != ESP_OK) {
      return rc;
    }
    const char* t = buf;
    char cmd;
    // Seek command in JSON { "cmd": "<command>...
    t = strstr (t, "{");
    if (t) {
      t = strstr (t + 1, "\"cmd\"");
      if (t) {
        t = strstr (t + 1, ":");
        if (t) {
          t = strstr (t + 1, "\"");
          if (t) {
            cmd = toupper(t[1]);
          }
        }
      }
    }
    if (!t) {
      httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Wrong POST request");
      return ESP_FAIL;
    }
    if (isTestEffectOn) {
      ESP_LOGI (TAG, "Apply command \'%c\' to test effect", cmd);
      ledEventLoop -> postInteractEvent (&cmd, sizeof (cmd));
    }
    else if (cmd == 'O') {
      ESP_LOGI (TAG, "Start test effect");
      ledEventLoop -> postStartEvent (testEffect);
      isTestEffectOn = true;
    }
  }

  httpd_resp_set_type (req, "application/json");

  sprintf (buf, "{\"state\": %d}", isTestEffectOn);
  ESP_LOGI (TAG, "Return = \"%s\"", buf);

  return httpd_resp_sendstr(req, buf);
}