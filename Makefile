CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude -Iinclude/core -Iinclude/entities -Iinclude/simulation -Iinclude/io -fsanitize=address -g -Wno-unknown-pragmas

# === Sources & Objects ===
SRCS      := main.cpp $(shell find src -name '*.cpp')
OBJS      := $(patsubst %.cpp, obj/%.o, $(SRCS))

TEST_SRCS := tests/main_test.cpp src/core/Matrix.cpp tests/test_matrix.cpp

.PHONY: all clean run test

# Cible par défaut
all: bin/linpp

# === Compilation rule for any .cpp (root or subfolders) ===
obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linking main app
bin/linpp: $(OBJS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile and link all tests
bin/run_tests: $(TEST_SRCS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -Itests $^ -o $@

# === Utility commands ===
clean:
	rm -rf obj bin

run: bin/linpp
	./bin/linpp

test: bin/run_tests
	./bin/run_tests