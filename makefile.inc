CC := gcc
AR := ar
RANLIB := ranlib

LINK_PATH := -L/usr/lib
LINK_FLAGS := $(LINK_PATH)
#LINK_FLAGS := -shared -fPIC -pipe -fpie
#LINK_FLAGS += -Wl,-z,relro,-z,now
#LINK_FLAGS += -lpthread -ldlt
#LINK_FLAGS += -lsystemd
LINK_FLAGS += -lm
#LINK_FLAGS += --sysroot=$(CROSS_SYSROOT)

INCLUDES := -I/usr/include
CFLAGS := -O3 -g -fasynchronous-unwind-tables -Wall -Wno-unused-function
#CFLAGS += -march=armv8-a+crypto -mtune=cortex-a57
#below option is included in "-O3"
#-ftree-vectorize
CFLAGS += -feliminate-unused-debug-types
#-fno-inline
#CFLAGS += -fstack-protector-strong
#CFLAGS += -D_FORTIFY_SOURCE=2
CFLAGS += -D_GNU_SOURCE=1
CFLAGS += $(INCLUDES)
#CFLAGS += --sysroot=$(CROSS_SYSROOT)

#export PATH := $(PATH):$(SYSROOTS)/$(BUILD)/usr/bin/$(TARGET)

