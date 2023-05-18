#!/bin/bash

# Directory containing the test files
TEST_DIR="test"

# Get the task number from the command-line parameter
TASK_NUMBER=$1

# Check if the task number is provided
if [[ -z $TASK_NUMBER ]]; then
echo "Please provide the task number as a parameter."
exit 1
fi

# Construct the subdirectory name based on the task number
TASK_DIR="task$TASK_NUMBER"

# Check if the task directory exists
if [[ ! -d "$TEST_DIR/$TASK_DIR" ]]; then
echo "Task directory '$TASK_DIR' does not exist."
exit 1
fi

# List all test files in the specified task directory
TEST_FILES=$(find "$TEST_DIR/$TASK_DIR" -type f)

# Array to store the names of failing tests
FAILING_TESTS=()

# Count the total number of test files
TOTAL_TESTS=$(echo "$TEST_FILES" | wc -l)
CURRENT_TEST=0

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

