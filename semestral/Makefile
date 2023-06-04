LINKER := g++ -fsanitize=address -std=c++17
COMPILER := g++ -g -fsanitize=address -std=c++17 -Wall -pedantic

SRC_FILES := $(wildcard ./src/*.cpp) $(wildcard ./src/*/*.cpp) $(wildcard ./src/*/*/*.cpp) $(wildcard ./src/*/*/*/*.cpp) $(wildcard ./src/*/*/*/*/*.cpp)
OBJ_FILES := $(patsubst ./src/%, ./obj/%, $(patsubst %.cpp, %.o, $(SRC_FILES)))

.PHONY: compile run doc clean

all: compile doc vavravl3_test
compile: vavravl3
run: vavravl3
	./vavravl3
doc: $(SRC_FILES)
	mkdir -p doc
	doxygen Doxyfile
clean:
	rm -rf obj vavravl3 vavravl3_test doc
vavravl3: $(filter-out ./obj/test/main.test.o,$(OBJ_FILES))
	$(LINKER) $^ -o $@
test: vavravl3_test
	./vavravl3_test
vavravl3_test: $(filter-out ./obj/main.o,$(OBJ_FILES))
	@$(LINKER) $^ -o $@
obj/%.o: src/%.cpp
	mkdir -p $(patsubst src/%,obj/%,$(dir $<))
	$(COMPILER) -c $< -o $@

obj/Makefile.deps:
	mkdir -p obj
	$($(COMPILER) -MM $(SRC_FILES)) > obj/Makefile.deps
-include obj/Makefile.deps
