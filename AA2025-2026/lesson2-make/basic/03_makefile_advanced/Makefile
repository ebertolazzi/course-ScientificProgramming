# ============================================================================
# ADVANCED MAKEFILE
# ============================================================================
# Features: pattern rules, auto dependencies, build directory,
#           conditional compilation, debug/release targets

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
DEPFLAGS = -MMD -MP

# Directories
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/hello

# Automatic source discovery
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Pattern substitution: src/file.cpp -> build/file.o
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Dependency files
DEPS = $(OBJS:.o=.d)

# Default target
.PHONY: all
all: $(TARGET)
	@echo "Build complete: $(TARGET)"

# Create build directory (order-only prerequisite)
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Link step
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Linked $@"

# Pattern rule: compile any .cpp to .o
# Generates .d dependency files automatically
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@
	@echo "Compiled $(notdir $@)"

# Include auto-generated dependency files
-include $(DEPS)

# Clean
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	@echo "Cleaned"

# Rebuild from scratch
.PHONY: rebuild
rebuild: clean all

# Debug build (override variables)
.PHONY: debug
debug: CXXFLAGS = -std=c++17 -g -O0 -DDEBUG
debug: clean all

# Release build
.PHONY: release
release: CXXFLAGS = -std=c++17 -O3 -DNDEBUG
release: clean all

# Show variables
.PHONY: info
info:
	@echo "Source files: $(SRCS)"
	@echo "Object files: $(OBJS)"
	@echo "Dependency files: $(DEPS)"
	@echo "Build directory: $(BUILD_DIR)"
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"

# Help
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make          - Build (release mode)"
	@echo "  make debug    - Build with debug symbols"
	@echo "  make release  - Build optimized"
	@echo "  make info     - Show build variables"
	@echo "  make clean    - Remove build files"
	@echo "  make rebuild  - Clean + build"
