# Simple project for static circular buffer library

## Run commands
```bash
# Clean build
rm -rf build        # Or "rmdir /s /q build" on Windows

# Generate build
cmake -S . -B build

# Build project
cmake --build build

# Run googletests
GTEST_COLOR=1 ctest --test-dir build --output-on-failure --j 12