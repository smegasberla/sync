# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Isrc/include -Isrc/args/include 

# Find all .cpp files recursively in src and its subdirectories
SRCS     := $(shell find src -type f -name "*.cpp")
TARGET   := fsync

# Default rule: build the executable
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean rule to remove the built executable
clean:
	rm -f $(TARGET)

.PHONY: all clean