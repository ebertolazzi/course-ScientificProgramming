# ============================================================================
# MULTI-DIRECTORY MAKEFILE
# ============================================================================

SRC_DIR = src
LIB_DIR = lib
INC_DIR = include
TEST_DIR = test
BUILD_DIR = build

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I$(INC_DIR)
AR = ar
ARFLAGS = rcs

LIB_SRCS = $(wildcard $(LIB_DIR)/*.cpp)
APP_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)

LIB_OBJS = $(LIB_SRCS:$(LIB_DIR)/%.cpp=$(BUILD_DIR)/%.o)
APP_OBJS = $(APP_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)

LIBRARY = $(BUILD_DIR)/libutils.a
PROGRAM = $(BUILD_DIR)/app
TEST_PROG = $(BUILD_DIR)/test_runner

.PHONY: all
all: $(PROGRAM)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Static library
$(LIBRARY): $(LIB_OBJS) | $(BUILD_DIR)
	$(AR) $(ARFLAGS) $@ $^

# Executable
$(PROGRAM): $(APP_OBJS) $(LIBRARY) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(APP_OBJS) -L$(BUILD_DIR) -lutils -o $@

# Compile rules
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test
.PHONY: test
test: $(TEST_PROG)
	./$(TEST_PROG)

$(TEST_PROG): $(TEST_OBJS) $(LIB_OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: run
run: $(PROGRAM)
	./$(PROGRAM)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: help
help:
	@echo "make         - Build application"
	@echo "make run     - Build and run"
	@echo "make test    - Build and run tests"
	@echo "make clean   - Remove build directory"
