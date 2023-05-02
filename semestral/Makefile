LINKER := g++
COMPILER := g++ -Wall -g -std=c++17 -Wall -pedantic

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
# pattern, replacement, text
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
BIN_FILE := $(BIN_DIR)/relgebra

.PHONY: all clean deps init

all: $(BIN_FILE) init

init:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

$(BIN_FILE): $(OBJ_FILES)
	$(LINKER) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COMPILER) -c $< -o $@

clean: init
	rm -rf $(OBJ_DIR)/*.o $(BIN_FILE) $(OBJ_DIR)/Makefile.deps

deps: init
	$(COMPILER) -MM $(SRC_FILES) > $(OBJ_DIR)/Makefile.deps

-include $(OBJ_DIR)/Makefile.deps