#!/bin/bash

# Directory containing the test files
TEST_DIR="test"

# List all subdirectories inside the test directory
TASK_DIRS=$(find "$TEST_DIR" -type d -name "task*")

# Array to store the names of failing tests
FAILING_TESTS=()

# Count the total number of test files
TOTAL_TESTS=$(find "$TEST_DIR" -type f | wc -l)
CURRENT_TEST=0

# Iterate over each task directory
for TASK_DIR in $TASK_DIRS; do
# List all test files in the current task directory
TEST_FILES=$(find "$TASK_DIR" -type f)

# Iterate over each test file
for TEST_FILE in $TEST_FILES; do
CURRENT_TEST=$((CURRENT_TEST + 1))
PERCENTAGE=$((CURRENT_TEST * 100 / TOTAL_TESTS))

echo -ne "Running tests: $PERCENTAGE% \r"

# Run the test using the hsh executable and discard null bytes
OUTPUT=$(./test/checker.bash ./hsh "$TEST_FILE" 2>/dev/null | tr -d '\0')

# Check if the output contains "OK" (indicating success)
if [[ "$OUTPUT" != *"OK"* ]]; then
FAILING_TESTS+=("$TEST_FILE")
fi
done
done

echo

# Print the list of failing tests
if [[ ${#FAILING_TESTS[@]} -eq 0 ]]; then
echo "All tests passed!"
else
echo "Failing tests:"
for FAILING_TEST in "${FAILING_TESTS[@]}"; do
echo "$FAILING_TEST"
done
fi
