USB2AMIGA_VARIANTS = CDTV CDTV_FF DB9 DB9_FF A500 A500_FF
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
	$(MAKE) all
	@$(LS) tmp/*/*.hex

$(USB2AMIGA_VARIANTS):
	$(MAKE) -C $@ -f ../arduino.mk all

