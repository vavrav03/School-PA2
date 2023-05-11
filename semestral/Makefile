LINKER := g++ -std=c++17 
COMPILER := g++ -g -std=c++17 -Wall -pedantic

SRC_FILES := $(shell find ./src -name '*.cpp')
# pattern, replacement, text
OBJ_FILES := $(patsubst ./src/%, ./obj/%, $(patsubst %.cpp, %.o, $(SRC_FILES)))

.PHONY: compile run doc clean test

compile: bin/relgebra
run: bin/relgebra
	./bin/relgebra
test: bin/relgebra_test
	./bin/relgebra_test
doc: $(SRC_FILES)
	mkdir -p doc
	doxygen Doxyfile
clean:
	rm -rf obj bin doc
bin/relgebra: $(filter-out obj/test/main.test.o,$(OBJ_FILES))
	@mkdir -p bin
	@$(LINKER) $^ -o $@
	@chmod +x $@
bin/relgebra_test: $(filter-out obj/main.o,$(OBJ_FILES))
# print all dependencies
	@mkdir -p bin
	@$(LINKER) $^ -o $@
	@chmod +x $@
obj/%.o: src/%.cpp
# create directory copying src structure in obj folder
	mkdir -p $(patsubst src/%,obj/%,$(dir $<))
	$(COMPILER) -c $< -o $@

obj/Makefile.deps:
	mkdir -p obj
	$($(COMPILER) -MM $(SRC_FILES)) > obj/Makefile.deps
-include obj/Makefile.deps
