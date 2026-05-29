# Source files for all distributions
SRC_DIR    = src
# Source files for specific OS versions
OS_DIR     = os
# Header files for all distributions
HEADER_DIR = include
# Output directory for built libraries
DIST_DIR   = dist
# Intermediate build directory
BUILD_DIR  = build
# Name of the library
LIB_NAME   = systemui
# Toolchain prefix
TOOLCHAIN  = sh4a_nofpueb-elf

SDK_DIR   ?= /sdk # Path to the SDK installation
OS        ?= 7002

SRC_DIRS := $(SRC_DIR) $(OS_DIR)/$(OS)

DEPS_DIR := $(BUILD_DIR)/$(OS)/deps
OBJ_DIR  := $(BUILD_DIR)/$(OS)/obj
LIB_DIR  := $(BUILD_DIR)/$(OS)/lib

OUT_DIR  := $(DIST_DIR)/$(OS)

DEPS_FLAGS=-MT $@ -MMD -MP -MF $(DEPS_DIR)/$*.d
WARNINGS=-Wall -Wextra -pedantic -Werror -pedantic-errors
INCLUDES=-I$(SDK_DIR)/include -I$(HEADER_DIR)
DEFINES=
FUNCTION_FLAGS=-fno-builtin -ffunction-sections -fdata-sections -gdwarf-5 -Os -flto -ffat-lto-objects

COMMON_FLAGS=$(FUNCTION_FLAGS) $(INCLUDES) $(WARNINGS) $(DEFINES)

AS_FLAGS := -gdwarf-5
CC_FLAGS  = -std=c23 $(COMMON_FLAGS)
CXX_FLAGS = -std=c++20 $(COMMON_FLAGS)
AR_FLAGS := rcs

AS:=sh4a_nofpueb-elf-gcc
CC:=$(TOOLCHAIN)-gcc
CXX:=$(TOOLCHAIN)-g++
AR:=$(TOOLCHAIN)-ar
READELF:=$(TOOLCHAIN)-readelf
OBJCOPY:=$(TOOLCHAIN)-objcopy
STRIP:=$(TOOLCHAIN)-strip

LIBS:=-L$(SDK_DIR) -lsdk

LIB_AR := $(LIB_DIR)/lib$(LIB_NAME).a

AS_SOURCES:=$(shell find $(SRC_DIRS) -name '*.S')
CC_SOURCES:=$(shell find $(SRC_DIRS) -name '*.c')
CXX_SOURCES:=$(shell find $(SRC_DIRS) -name '*.cpp')
OBJECTS := $(addprefix $(OBJ_DIR)/,$(AS_SOURCES:.S=.o)) \
	$(addprefix $(OBJ_DIR)/,$(CC_SOURCES:.c=.o)) \
	$(addprefix $(OBJ_DIR)/,$(CXX_SOURCES:.cpp=.o))

DEPFILES := $(OBJECTS:$(OBJ_DIR)/%.o=$(DEPS_DIR)/%.d)

lib: $(LIB_AR) Makefile
all: tar

.DEFAULT_GOAL := all
.SECONDARY: # Prevents intermediate files from being deleted

.NOTPARALLEL: clean
clean:
	@echo $(SRC_DIRS)
	rm -rf $(BUILD_DIR) $(DIST_DIR)

dist: lib
	@mkdir -p $(OUT_DIR)/lib
	cp $(LIB_AR) $(OUT_DIR)/lib/
	cp -r $(HEADER_DIR) $(OUT_DIR)

tar: dist
	tar -czf $(DIST_DIR)/$(LIB_NAME)-$(OS).tar.gz -C $(OUT_DIR) .

$(LIB_AR): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

$(OBJ_DIR)/%.o: %.S
	@mkdir -p $(dir $@)
	$(AS) -c $< -o $@ $(AS_FLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEPS_DIR)/$<)
	+$(CC) -c $< -o $@ $(CC_FLAGS) $(DEPFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEPS_DIR)/$<)
	+$(CXX) -c $< -o $@ $(CXX_FLAGS) $(DEPFLAGS)

compile_commands.json:
	@$(MAKE) OS=$(OS) clean
	bear -- sh -c "$(MAKE) $(MAKEFLAGS) OS=$(OS) --keep-going all || exit 0"


.PHONY: phony lib all clean compile_commands.json

-include $(DEPFILES)
