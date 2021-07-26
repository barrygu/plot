SUBDIRS := lib cli examples
SUBDIRS_CLEAN := $(addsuffix .clean,$(SUBDIRS))

export TOPDIR := $(PWD)

all: $(SUBDIRS)

.PHONY: $(SUBDIRS) $(SUBDIRS_C)

$(SUBDIRS):
	make -C $@

clean: $(SUBDIRS_CLEAN)

$(SUBDIRS_CLEAN):
	-make -C $(basename $@) clean
