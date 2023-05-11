LINKER := g++
COMPILER := g++ -Wall -g -std=c++17 -Wall -pedantic

SRC_FILES := $(wildcard src/*.cpp)
# pattern, replacement, text
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,$(SRC_FILES))

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
bin/relgebra: src/main.cpp
	mkdir -p bin
	$(LINKER) $^ -o $@
	chmod +x $@
bin/relgebra_test: src/main.test.cpp
	mkdir -p bin
	$(LINKER) $^ -o $@
	chmod +x $@
obj/%.o: src/%.cpp
	$(COMPILER) -c $< -o $@

obj/Makefile.deps:
	mkdir -p obj
	$(COMPILER) -MM $(SRC_FILES) > obj/Makefile.deps
-include obj/Makefile.deps