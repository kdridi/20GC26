# Pong - Makefile
# Build system with coverage and benchmarking support

CXX := clang++
CLANG_TIDY := /opt/homebrew/opt/llvm/bin/clang-tidy

# Base flags (DRY - used by all targets)
BASE_CXXFLAGS := -std=c++2c -Wall -Wextra -Wpedantic -Werror -I/opt/homebrew/include
BASE_LDFLAGS := -L/opt/homebrew/lib

# Profile-specific flags
DEBUG_FLAGS := -g -fsanitize=address,undefined
RELEASE_FLAGS := -O3 -DNDEBUG
COVERAGE_FLAGS := -fprofile-arcs -ftest-coverage

# Libraries
LIBS := -lgtest -lgtest_main
BENCH_LIBS := -lbenchmark -lpthread

# Directories
SRC_DIR := pong
TEST_DIR := tests
BENCH_DIR := benchmarks
BUILD_DIR := build
COVERAGE_DIR := coverage

# Sources
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
BENCH_SRCS := $(wildcard $(BENCH_DIR)/*.cpp)

# Targets
PONG_EXE := $(BUILD_DIR)/pong
TEST_EXE := $(BUILD_DIR)/test_runner
BENCH_EXE := $(BUILD_DIR)/bench_runner
TEST_COV_EXE := $(BUILD_DIR)/test_coverage

# Default to debug
CXXFLAGS := $(BASE_CXXFLAGS) $(DEBUG_FLAGS)
LDFLAGS := $(BASE_LDFLAGS) $(DEBUG_FLAGS)

.PHONY: all clean test run coverage bench release help format format-check lint check-all

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

# Release build (override with release flags)
release: CXXFLAGS := $(BASE_CXXFLAGS) $(RELEASE_FLAGS)
release: LDFLAGS := $(BASE_LDFLAGS)
release: clean all

# Coverage build and report (override, no sanitizers)
coverage: CXXFLAGS := $(BASE_CXXFLAGS) $(COVERAGE_FLAGS)
coverage: LDFLAGS := $(BASE_LDFLAGS) $(COVERAGE_FLAGS)
coverage: $(BUILD_DIR)
	@echo "Building tests with coverage..."
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) -o $(TEST_COV_EXE) $(LDFLAGS) $(LIBS)
	@echo "Running tests with coverage..."
	@mkdir -p $(COVERAGE_DIR)
	@cd $(BUILD_DIR) && ./test_coverage
	@echo "Generating coverage report..."
	@lcov --capture --directory . --output-file $(COVERAGE_DIR)/coverage.info \
		--rc lcov_branch_coverage=1 \
		--ignore-errors inconsistent,format,negative 2>&1 | grep -v "WARNING\|ignor" || true
	@lcov --remove $(COVERAGE_DIR)/coverage.info '/usr/*' '/opt/homebrew/*' \
		--output-file $(COVERAGE_DIR)/coverage.info \
		--rc lcov_branch_coverage=1 \
		--ignore-errors inconsistent,format 2>&1 | grep -v "WARNING" || true
	@genhtml $(COVERAGE_DIR)/coverage.info --output-directory $(COVERAGE_DIR) \
		--branch-coverage
	@echo "✅ Coverage report: $(COVERAGE_DIR)/index.html"

# Benchmarks (optimized build)
bench: CXXFLAGS := $(BASE_CXXFLAGS) $(RELEASE_FLAGS)
bench: LDFLAGS := $(BASE_LDFLAGS)
bench: $(BUILD_DIR)
	@echo "Building benchmarks..."
	$(CXX) $(CXXFLAGS) $(BENCH_SRCS) -o $(BENCH_EXE) $(LDFLAGS) $(BENCH_LIBS)
	@echo "Running benchmarks..."
	@$(BENCH_EXE)

# Code quality targets
format:
	@echo "Formatting code..."
	@find $(SRC_DIR) $(TEST_DIR) $(BENCH_DIR) -name "*.cpp" -o -name "*.hpp" 2>/dev/null | \
		xargs clang-format -i || true
	@echo "✅ Code formatted"

format-check:
	@echo "Checking code format..."
	@FAILED=0; \
	for file in $$(find $(SRC_DIR) $(TEST_DIR) $(BENCH_DIR) -name "*.cpp" -o -name "*.hpp" 2>/dev/null); do \
		if ! clang-format --dry-run --Werror "$$file" >/dev/null 2>&1; then \
			echo "❌ Format check failed: $$file"; \
			clang-format --dry-run "$$file" | head -20; \
			FAILED=1; \
		fi; \
	done; \
	if [ $$FAILED -eq 1 ]; then \
		echo "Run 'make format' to fix formatting issues."; \
		exit 1; \
	fi
	@echo "✅ Format check passed"

lint:
	@echo "Running clang-tidy..."
	@$(CLANG_TIDY) $(SRC_DIR)/*.cpp $(TEST_DIR)/*.cpp -- $(BASE_CXXFLAGS) || \
		(echo "❌ Linting failed" && exit 1)
	@echo "Running cppcheck..."
	@cppcheck --enable=warning,style,performance,portability \
		--suppress=missingIncludeSystem --suppress=unusedFunction \
		--inline-suppr --quiet --error-exitcode=1 \
		$(SRC_DIR) $(TEST_DIR) 2>&1 || \
		(echo "❌ cppcheck failed" && exit 1)
	@echo "✅ Lint passed"

check-all: format-check lint test
	@echo "✅ All checks passed!"

clean:
	rm -rf $(BUILD_DIR) $(COVERAGE_DIR)
	find . -name "*.gcda" -o -name "*.gcno" | xargs rm -f 2>/dev/null || true

help:
	@echo "Pong Makefile"
	@echo ""
	@echo "Build Targets:"
	@echo "  all         - Build Pong (default, debug)"
	@echo "  test        - Build and run tests"
	@echo "  coverage    - Run tests with coverage report (HTML)"
	@echo "  bench       - Run performance benchmarks"
	@echo "  run         - Run Pong"
	@echo "  release     - Build optimized release"
	@echo "  clean       - Remove build artifacts"
	@echo ""
	@echo "Quality Targets:"
	@echo "  format      - Format code with clang-format"
	@echo "  format-check- Check code format (fails if not formatted)"
	@echo "  lint        - Run clang-tidy + cppcheck"
	@echo "  check-all   - Run all checks (format + lint + test)"
	@echo ""
	@echo "  help        - Show this message"
