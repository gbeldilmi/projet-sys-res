#------------------------------------------------------------------------------#
# Project name                                                                 #
#------------------------------------------------------------------------------#
PROJECT_NAME        := game
BINARY_FILE         := $(PROJECT_NAME)

#------------------------------------------------------------------------------#
# Source files                                                                 #
#------------------------------------------------------------------------------#
INCLUDE_DIR         := inc
SOURCE_DIR          := src
BUILD_DIR           := bin
H_FILES             := $(wildcard $(INCLUDE_DIR)/*.h)
C_FILES             := $(wildcard $(SOURCE_DIR)/*.c)
O_FILES             := $(C_FILES:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)

#------------------------------------------------------------------------------#
# Options for code generation                                                  #
#------------------------------------------------------------------------------#
INCLUDES_FLAGS      := -I $(INCLUDE_DIR)/
LIBRARIES_FLAGS     := -lpthread
C_FLAGS             := -v -Wall -Werror -Wextra -O3
LD_FLAGS            := -v

#------------------------------------------------------------------------------#
# Commands                                                                     #
#------------------------------------------------------------------------------#
.PHONY : all, clean, re
all : $(BUILD_DIR)/$(BINARY_FILE)
clean :
	rm -frv $(BUILD_DIR)
re : clean all

#------------------------------------------------------------------------------#
# Dependencies                                                                 #
#------------------------------------------------------------------------------#
$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c
	mkdir -pv $(dir $@)
	gcc $(C_FLAGS) -c $< -o $@ $(INCLUDES_FLAGS)
$(BUILD_DIR)/$(BINARY_FILE) : $(O_FILES)
	gcc $(LD_FLAGS) $^ -o $@ $(LIBRARIES_FLAGS)
