# Makefile for the C++ assembler library

# Archiver and compiler
AR = ar
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Target library
TARGET = libcpp-assembler.a

# Source and object files
SRC = tokenizer.cpp assembler.cpp symbol.cpp
OBJ = $(SRC:.cpp=.o)

# Test files
TEST_SRC = test_assembler.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_TARGET = test_assembler

# Phony targets
.PHONY: all clean test

# Default target
all: $(TARGET)

# Rule to create the static library
$(TARGET): $(OBJ)
	$(AR) rcs $@ $^

# Rule to compile C++ source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build the test executable
test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ) $(TARGET)
	$(CXX) -o $@ $(TEST_OBJ) $(TARGET)

# Rule to clean up build artifacts
clean:
	rm -f $(OBJ) $(TARGET) $(TEST_OBJ) $(TEST_TARGET)
