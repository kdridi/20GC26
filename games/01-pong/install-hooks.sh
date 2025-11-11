#!/bin/bash
# Install git hooks for Pong

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
GIT_ROOT="$(git rev-parse --show-toplevel)"
HOOKS_DIR="$GIT_ROOT/.git/hooks"

echo "Installing git hooks..."

# Make hook executable
chmod +x "$SCRIPT_DIR/.pre-commit-hook.sh"

# Install pre-commit hook
if [ -f "$HOOKS_DIR/pre-commit" ]; then
    echo "⚠️  pre-commit hook already exists"
    read -p "   Overwrite? (y/N): " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo "❌ Installation cancelled"
        exit 1
    fi
fi

ln -sf "$SCRIPT_DIR/.pre-commit-hook.sh" "$HOOKS_DIR/pre-commit"

echo "✅ Git hooks installed successfully!"
echo ""
echo "The pre-commit hook will run:"
echo "  - make format-check"
echo "  - make lint
echo "  - make test"
echo ""
echo "To bypass: git commit --no-verify (not recommended)"
