USB2AMIGA_VARIANTS = CDTV DB9 A500
BUILD_BASE      := $(abspath $(lastword $(MAKEFILE_LIST))/..)/tmp

RM = rm -rf
CP = cp -v
LS = ls -l

.PHONY: $(USB2AMIGA_VARIANTS)

all: $(USB2AMIGA_VARIANTS)

clean:
	$(RM) $(BUILD_BASE)

release:
	$(MAKE) clean
	$(MAKE) all CFLAGS+=-DDEBUG=0 CXXFLAGS+=-DDEBUG=0
	@$(LS) tmp/*/*.hex

$(USB2AMIGA_VARIANTS):
	$(MAKE) -C $@ -f ../arduino.mk all

