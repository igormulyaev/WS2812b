idf_component_register (
  SRCS 
    "main.cpp"
    "led_base.cpp"
    "led_event_loop.cpp"
    "effects/christmas_tree.cpp"
    "effects/fire_effect.cpp"
    "effects/stars_effect.cpp"
    "effects/test_effect.cpp"
    "net_base.cpp"
    "http_server.cpp"
  INCLUDE_DIRS 
    "."
)

set(WEB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../web")

if(EXISTS ${WEB_SRC_DIR})
    spiffs_create_partition_image(www ${WEB_SRC_DIR} FLASH_IN_PROJECT)
else()
    message(FATAL_ERROR "${WEB_SRC_DIR} doesn't exit. Please create it.")
endif()
