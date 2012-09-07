MODULE := engines/hopkins

MODULE_OBJS := \
	detection.o \
	files.o \
	globals.o \
	hopkins.o 

# This module can be built as a plugin
ifeq ($(ENABLE_HOPKINS), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
