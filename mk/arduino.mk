BOARD_TAG        = pro328
MONITOR_PORT     = /dev/ttyUSB0
ARDUINO_LIBS     = USB_Host_Shield_Library_2.0
MONITOR_BAUDRATE = 57600
USER_LIB_PATH    = $(HOME)/Arduino/libraries
OBJDIR           = $(BUILD_BASE)/$(USB2AMIGA_VARIANT)
CFLAGS          += -DUSB2AMIGA_VARIANT=$(USB2AMIGA_VARIANT) -DDEBUG=0 -Wall -Werror -Wno-error=sign-compare -Wno-error=unused-variable
CXXFLAGS        += -DUSB2AMIGA_VARIANT=$(USB2AMIGA_VARIANT) -DDEBUG=0 -Wall -Werror -Wno-error=sign-compare -Wno-error=unused-variable

include /usr/share/arduino/Arduino.mk
