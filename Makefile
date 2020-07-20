USB2AMIGA_VARIANTS = CDTV
BUILD_BASE      := $(abspath $(lastword $(MAKEFILE_LIST))/..)/tmp

RM = rm -rf
CP = cp -v
LS = ls -l

.PHONY: $(USB2AMIGA_VARIANTS)

all: $(USB2AMIGA_VARIANTS)

clean:
	$(RM) $(BUILD_BASE)

release:
	@if git status | grep '[	 ]USB2Amiga/'; then \
	   echo -e "\n*** source code contains uncommitted changes\n"; \
           exit 1; \
        fi
	$(MAKE) clean
	$(MAKE) all
	for r in $(USB2AMIGA_VARIANTS); do $(CP) $(BUILD_BASE)/$$r/USB2Amiga.hex hex/USB2Amiga.$$r.hex; done
	git add hex/

CDTV:
	$(MAKE) -C $@ -f ../arduino.mk all
	$(LS) $(BUILD_BASE)/$@/*.hex

