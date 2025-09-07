# Define variables
CC = gcc
CXX = g++
CFLAGS = -Wall -g
CXXFLAGS = -Wall -g
LDFLAGS =

TARGET = main.exe
SRCS = main.cpp timeManager.cc
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Rule to compile C source files into object files
%.o: %.c
	$(CXX) $(CFLAGS) -c $< -o $@

# Rule to compile C++ source files into object files (if applicable)
# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)

# Run target
run: $(TARGET)
	./$(TARGET)

# Phony targets to prevent conflicts with files of the same name
.PHONY: all clean run