idf_component_register (
  SRCS 
    "main.cpp"
    "led/led_base.cpp"
    "led/led_event_loop.cpp"
    "led/rmt_led.cpp"
    "effects/christmas_tree_effect.cpp"
    "effects/fire_effect.cpp"
    "effects/stars_effect.cpp"
    "effects/test_effect.cpp"
    "effects/debug_effect.cpp"
    "net_base.cpp"
    "http_server/http_server.cpp"
    "http_server/uri_handler.cpp"
    "http_server/sysinfo_handler.cpp"
    "http_server/default_handler.cpp"
    "http_server/hs_test_led.cpp"
    "http_server/hs_simple_effects.cpp"
    "button_base.cpp"
  INCLUDE_DIRS 
    "."
)

set(WEB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../web")

if(EXISTS ${WEB_SRC_DIR})
    spiffs_create_partition_image(www ${WEB_SRC_DIR} FLASH_IN_PROJECT)
else()
    message(FATAL_ERROR "${WEB_SRC_DIR} doesn't exit. Please create it.")
endif()
