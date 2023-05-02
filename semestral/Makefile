LINKER := g++
COMPILER := g++ -Wall -g -std=c++17 -Wall -pedantic

SRC_DIR := src
OBJ_DIR := obj
TEST_OBJ_DIR := test_obj
BIN_DIR := bin
DOC_DIR := doc

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
# pattern, replacement, text
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TEST_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(TEST_OBJ_DIR)/%.o,$(SRC_FILES))
BIN_FILE := $(BIN_DIR)/relgebra
TEST_BIN_FILE := $(BIN_DIR)/relgebra_test

.PHONY: all clean deps init run doc

$(BIN_FILE): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(LINKER) $^ -o $@
	chmod +x $@
$(TEST_BIN_FILE): $(TEST_OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(LINKER) $^ -o $@
	chmod +x $@
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COMPILER) -c $< -o $@
$(TEST_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(TEST_OBJ_DIR)
	$(COMPILER) -D__TESTING_MACRO_RELGEBRA__ -c $< -o $@

$(OBJ_DIR)/Makefile.deps:
	mkdir -p $(OBJ_DIR)
	$(COMPILER) -MM $(SRC_FILES) > $(OBJ_DIR)/Makefile.deps

all: $(BIN_FILE)
run: $(BIN_FILE)
	./$(BIN_FILE)
doc: $(SRC_FILES)
	mkdir -p $(DOC_DIR)
	doxygen Doxyfile
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(DOC_DIR)
test: $(TEST_BIN_FILE)
	./$(TEST_BIN_FILE)

-include $(OBJ_DIR)/Makefile.deps