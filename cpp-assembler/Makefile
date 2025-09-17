# Makefile for the C++ assembler library and test

# Archiver and compiler
AR = ar
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Library target
LIB_TARGET = libcpp-assembler.a
LIB_SRC = tokenizer.cpp assembler.cpp symbol.cpp linker.cpp
LIB_OBJ = $(LIB_SRC:.cpp=.o)

# Test target
TEST_TARGET = assembler_test
TEST_SRC = test_assembler.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Phony targets
.PHONY: all clean test

# Default target
all: $(LIB_TARGET)

# Rule to create the static library
$(LIB_TARGET): $(LIB_OBJ)
	$(AR) rcs $@ $^

# Rule to compile C++ source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build and run the test executable
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ) $(LIB_TARGET)
	$(CXX) -o $@ $(TEST_OBJ) $(LIB_TARGET)

# Rule to clean up build artifacts
clean:
	rm -f $(LIB_OBJ) $(LIB_TARGET) $(TEST_OBJ) $(TEST_TARGET)
