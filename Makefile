# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Exec's name
TARGET = malloc

# Src files and object files
SRCS = main.cpp hashTable.cpp bMalloc.cpp test.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean rule to remove generated files
.PHONY: clean
clean:
	rm -rf $(OBJS) $(TARGET)