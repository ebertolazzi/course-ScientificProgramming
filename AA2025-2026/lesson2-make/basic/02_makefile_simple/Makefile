# ============================================================================
# SIMPLE MAKEFILE
# ============================================================================
# The most basic Makefile showing rules, variables, and automatic variables.

# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = hello
SRC_DIR = src

# Default target (first target in file)
.PHONY: all
all: $(TARGET)
	@echo "Build complete: ./$(TARGET)"

# Link step
# $@ = target name (hello)
# $^ = all prerequisites (hello.o mymath.o)
$(TARGET): hello.o mymath.o
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Linked $@"

# Compile step
# $< = first prerequisite (src/hello.cpp)
hello.o: $(SRC_DIR)/hello.cpp $(SRC_DIR)/mymath.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled $@"

mymath.o: $(SRC_DIR)/mymath.cpp $(SRC_DIR)/mymath.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled $@"

# Clean target (phony: not a real file)
.PHONY: clean
clean:
	rm -f *.o $(TARGET)
	@echo "Cleaned"

# Help
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make        - Build the program"
	@echo "  make clean  - Remove build files"
	@echo "  make help   - Show this help"
	@echo ""
	@echo "Automatic variables:"
	@echo "  "'$$@'" = target name"
	@echo "  "'$$<'" = first prerequisite"
	@echo "  "'$$^'" = all prerequisites"
	@echo "  "'$$?'" = prerequisites newer than target"
