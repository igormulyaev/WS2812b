#include "http_server.h"
#include "esp_log.h"
#include "led_base.h"
#include "led_event_loop.h"
#include "effects/christmas_tree_effect.h"
#include "effects/stars_effect.h"

// -----------------------------------------------------
esp_err_t HttpServer :: simpleEffectsGetUriHandler (httpd_req_t* req)
{
  ESP_LOGI (TAG, "Get simple_effects");
  HttpServer* srv = static_cast <HttpServer*> (req -> user_ctx);
  return srv -> simpleEffectsExecute (false, req);
}

// -----------------------------------------------------
esp_err_t HttpServer :: simpleEffectsPostUriHandler (httpd_req_t* req)
{
  ESP_LOGI (TAG, "Post simple_effects");
  HttpServer* srv = static_cast <HttpServer*> (req -> user_ctx);
  return srv -> simpleEffectsExecute (true, req);
}

// -----------------------------------------------------
esp_err_t HttpServer :: simpleEffectsExecute (bool isPost, httpd_req_t* req)
{
  const LedEffect* curEffect = ledEventLoop -> getLedEffect();
  const char* effectName = curEffect? curEffect -> getName(): "";

  if (isPost) {
    esp_err_t rc = readPostData (req);
    if ( rc != ESP_OK) {
      return rc;
    }
    char* t = buf;
    const char* cmdEffect = NULL;
    // Seek command in JSON { "cmd": "<cmd_effect>"...
    t = strstr (t, "{");
    if (t) {
      t = strstr (t + 1, "\"cmd\"");
      if (t) {
        t = strstr (t + 1, ":");
        if (t) {
          t = strstr (t + 1, "\"");
          if (t) {
            cmdEffect = ++t;
            t = strstr (t, "\"");
            if (t) {
              *t = '\0';
            }
          }
        }
      }
    }
    if (!t) {
      httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Wrong POST request");
      return ESP_FAIL;
    }
    ESP_LOGI (TAG, "Cmd effect = \"%s\"", cmdEffect);

    LedEffect* newEffect = NULL;

    if (strcmp (cmdEffect, ChristmasTreeEffect :: name) == 0) {
      newEffect = christmasTreeEffect;
    }
    else if (strcmp (cmdEffect, StarsEffect :: name) == 0) {
      newEffect = starsEffect;
    }
    if (newEffect) {
      effectName = newEffect -> getName();
      ESP_LOGI (TAG, "Start effect \"%s\"", effectName);
      ledEventLoop -> startEventAction (&newEffect);
    }
  }

  httpd_resp_set_type (req, "application/json");

  sprintf (buf, "{\"effect\": \"%s\"}", effectName);
  ESP_LOGI (TAG, "Return = \"%s\"", buf);

  return httpd_resp_sendstr(req, buf);
}