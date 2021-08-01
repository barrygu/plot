SUBDIRS := lib cli examples
SUBDIRS_CLEAN := $(addsuffix .clean,$(SUBDIRS))

export TOPDIR := $(PWD)

all: $(SUBDIRS)

.PHONY: $(SUBDIRS) $(SUBDIRS_C)

cli examples: lib
$(SUBDIRS):
	$(MAKE) -C $@

clean: $(SUBDIRS_CLEAN)

$(SUBDIRS_CLEAN):
	-$(MAKE) -C $(basename $@) clean
