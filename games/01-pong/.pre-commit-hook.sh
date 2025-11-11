#!/bin/bash
# Pre-commit hook for Pong
# Runs format-check and lint before allowing commit

set -e

echo "🔍 Running pre-commit checks..."

cd "$(git rev-parse --show-toplevel)/games/01-pong"

# Run format check
echo "  → Checking code format..."
if ! make format-check >/dev/null 2>&1; then
    echo ""
    echo "❌ Code format check failed!"
    echo "   Run 'make format' to fix formatting issues."
    echo "   Or run 'git commit --no-verify' to bypass (not recommended)."
    exit 1
fi

# Run lint (clang-tidy + cppcheck)
echo "  → Running linters..."
if ! make lint >/dev/null 2>&1; then
    echo ""
    echo "❌ Linting failed!"
    echo "   Fix the issues reported above."
    echo "   Or run 'git commit --no-verify' to bypass (not recommended)."
    exit 1
fi

# Run tests
echo "  → Running tests..."
if ! make test >/dev/null 2>&1; then
    echo ""
    echo "❌ Tests failed!"
    echo "   Fix the failing tests before committing."
    echo "   Or run 'git commit --no-verify' to bypass (not recommended)."
    exit 1
fi

echo "✅ All pre-commit checks passed!"
exit 0
