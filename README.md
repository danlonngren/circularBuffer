# Simple project for static and dynamic circular buffer library

## Run commands
```bash
# Clean build
rm -rf build

# Generate build
cmake -DBUILD_TESTS=ON -S . -B build

# Build project
cmake --build build

# Run googletests
GTEST_COLOR=1 ctest --test-dir build --output-on-failure --j 12

# Single command
rm -rf build && cmake -DBUILD_TESTS=ON -S . -B build && cmake --build build && \
GTEST_COLOR=1 ctest --test-dir build --output-on-failure --j 12

