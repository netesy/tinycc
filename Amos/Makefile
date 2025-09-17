CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS :=

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,src/%.o,$(SRCS))
TARGET := amos_linker

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f src/*.o $(TARGET)
