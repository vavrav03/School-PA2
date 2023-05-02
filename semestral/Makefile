LINKER := g++
COMPILER := g++ -Wall -g -std=c++17 -Wall -pedantic

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
DOR_DIR := doc

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
# pattern, replacement, text
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
BIN_FILE := $(BIN_DIR)/relgebra

.PHONY: all clean deps init run doc

$(BIN_FILE): $(OBJ_FILES)
	$(LINKER) $^ -o $@
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COMPILER) -c $< -o $@

all: init $(BIN_FILE)
init:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
run: $(BIN_FILE)
	./$(BIN_FILE)
doc: init $(SRC_FILES)
	doxygen Doxyfile
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(DOC_DIR)
deps: init
	$(COMPILER) -MM $(SRC_FILES) > $(OBJ_DIR)/Makefile.deps

-include $(OBJ_DIR)/Makefile.deps