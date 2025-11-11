# Pong - Makefile Simple
# Fallback tant que build2/bpkg n'est pas fonctionnel

CXX := clang++
CXXFLAGS := -std=c++2c -Wall -Wextra -Wpedantic -Werror
CXXFLAGS += -I/opt/homebrew/include
LDFLAGS := -L/opt/homebrew/lib
LIBS := -lgtest -lgtest_main

# Directories
SRC_DIR := pong
TEST_DIR := tests
BUILD_DIR := build

# Debug flags (default)
DEBUG_FLAGS := -g -fsanitize=address,undefined
RELEASE_FLAGS := -O3 -DNDEBUG

# Default to debug
CXXFLAGS += $(DEBUG_FLAGS)
LDFLAGS += $(DEBUG_FLAGS)

# Sources
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)

# Targets
PONG_EXE := $(BUILD_DIR)/pong
TEST_EXE := $(BUILD_DIR)/test_runner

.PHONY: all clean test run

all: $(PONG_EXE)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Build main executable
$(PONG_EXE): $(SRC_DIR)/main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# Build and run tests
$(TEST_EXE): $(TEST_SRCS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) -o $@ $(LDFLAGS) $(LIBS)

test: $(TEST_EXE)
	@echo "Running tests..."
	@$(TEST_EXE)

run: $(PONG_EXE)
	@$(PONG_EXE)

clean:
	rm -rf $(BUILD_DIR)

# Release build
release: CXXFLAGS := -std=c++2c -Wall -Wextra -Wpedantic -Werror $(RELEASE_FLAGS)
release: LDFLAGS := -L/opt/homebrew/lib
release: clean all

help:
	@echo "Pong Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  all     - Build Pong (default, debug)"
	@echo "  test    - Build and run tests"
	@echo "  run     - Run Pong"
	@echo "  release - Build optimized release"
	@echo "  clean   - Remove build artifacts"
	@echo "  help    - Show this message"
