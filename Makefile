USB2AMIGA_VARIANTS = CDTV
export BUILD_BASE = $(HOME)/tmp

RM = rm -rf
CP = cp -v

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
	$(MAKE) -C USB2Amiga -f ../mk/CDTV.mk all

