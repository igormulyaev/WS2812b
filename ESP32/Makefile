#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := Mu-FastLED-idf

EXTRA_COMPONENT_DIRS = $(IDF_PATH)/examples/common_components/protocol_examples_common

include $(IDF_PATH)/make/project.mk

WEB_SRC_DIR = $(shell pwd)/web
ifneq ($(wildcard $(WEB_SRC_DIR)/.*),)
SPIFFS_IMAGE_FLASH_IN_PROJECT := 1
$(eval $(call spiffs_create_partition_image,www,$(WEB_SRC_DIR)))
else
$(error $(WEB_SRC_DIR) doesn't exist. Please create it.)
endif
