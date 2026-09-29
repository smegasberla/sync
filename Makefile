# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

# Source files and executable name
SRCS     := src/main.cpp src/common.cpp
TARGET   := sync

# Default rule: build the executable
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean rule to remove the built executable
clean:
	rm -f $(TARGET)

.PHONY: all clean