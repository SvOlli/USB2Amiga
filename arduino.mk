#
# wrapper for arduino-mk
#
# written by SvOlli
# distributed under the terms of the GPLv3 or later
#

BOARD_TAG          = pro328
MONITOR_PORT       = /dev/ttyUSB0
ARDUINO_LIBS       = USB_Host_Shield_Library_2.0
MONITOR_BAUDRATE   = 57600
BUILD_BASE        := $(abspath $(lastword $(MAKEFILE_LIST))/..)/tmp
USB2AMIGA_VARIANT := $(notdir $(CURDIR))
USER_LIB_PATH      = $(HOME)/Arduino/libraries
OBJDIR             = $(BUILD_BASE)/$(USB2AMIGA_VARIANT)
CFLAGS            += -DUSB2AMIGA_VARIANT=$(USB2AMIGA_VARIANT) -DDEBUG=0 -Wall -Werror -Wno-error=sign-compare -Wno-error=unused-variable
CXXFLAGS          += -DUSB2AMIGA_VARIANT=$(USB2AMIGA_VARIANT) -DDEBUG=0 -Wall -Werror -Wno-error=sign-compare -Wno-error=unused-variable -std=c++11

include /usr/share/arduino/Arduino.mk

debugmk:
	@echo $(current_dir)
	@echo "$(.VARIABLES)"
	false
