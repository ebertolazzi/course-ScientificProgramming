# ============================================================================
# MAKEFILE: FUNCTIONS, CONDITIONALS, PLATFORM DETECTION
# ============================================================================

# ---- User-defined functions ----
# $(call function_name,arg1,arg2)

cpp_to_o = $(patsubst %.cpp,%.o,$(1))
basename_fn = $(basename $(notdir $(1)))

# ---- Conditional build ----
DEBUG ?= 0
ifeq ($(DEBUG),1)
    CXXFLAGS = -std=c++17 -g -O0 -DDEBUG
    BUILD_TYPE = debug
else
    CXXFLAGS = -std=c++17 -O3 -DNDEBUG
    BUILD_TYPE = release
endif

# Feature flags
USE_FEATURE_X ?= 0
ifeq ($(USE_FEATURE_X),1)
    CXXFLAGS += -DUSE_FEATURE_X
endif

# ---- Platform detection ----
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CXXFLAGS += -DLINUX
    LDFLAGS += -lpthread
endif
ifeq ($(UNAME_S),Darwin)
    CXXFLAGS += -DMACOS
endif

# ---- Compiler detection ----
CXX = g++
CXX_VERSION := $(shell $(CXX) --version 2>&1 | head -1)

# ---- Multi-line macro ----
define COMPILE_MSG
@echo "========================================"
@echo "Compiling: $(1)"
@echo "Compiler:  $(CXX_VERSION)"
@echo "Build:     $(BUILD_TYPE)"
@echo "Platform:  $(UNAME_S)"
@echo "========================================"
endef

# ---- Sources ----
SRCS = $(wildcard src/*.cpp)
OBJS = $(call cpp_to_o,$(SRCS))
TARGET = program

.PHONY: all
all: $(TARGET)
	@echo "Build complete: $(BUILD_TYPE)"

$(TARGET): $(OBJS)
	$(call COMPILE_MSG,$@)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ---- Dependency generation ----
%.d: %.cpp
	@$(CXX) $(CXXFLAGS) -MM $< | sed 's|$(notdir $*\.o)|$*\.o|' > $@
-include $(SRCS:.cpp=.d)

# ---- Utility targets ----
.PHONY: info
info:
	@echo "Source files: $(SRCS)"
	@echo "Object files: $(OBJS)"
	@echo "Build type:   $(BUILD_TYPE)"
	@echo "Platform:     $(UNAME_S)"
	@echo "CXX:          $(CXX)"
	@echo "CXXFLAGS:     $(CXXFLAGS)"

.PHONY: debug
debug:
	$(MAKE) DEBUG=1

.PHONY: feature-x
feature-x:
	$(MAKE) USE_FEATURE_X=1

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET) *.d
