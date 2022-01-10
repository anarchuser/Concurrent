# Simple Makefile providing a simple interface for cmake. Oh, sweet irony

BUILD_DIR = cmake-build

.PHONY = all setup build run test

# Build then test then run
all:	test	run

# Initialise cmake build files at BUILD_DIR
setup:	CMakeLists.txt
	cmake -H. -B$(BUILD_DIR)

# Build the project (lib and src)
build:	setup
	cmake --build $(BUILD_DIR) --target Concurrent

# Build the benchmarking tool
run:	build
	./$(BUILD_DIR)/Concurrent

# Build and run the tests
test:	build
	cmake --build $(BUILD_DIR) --target Test
	./$(BUILD_DIR)/Test