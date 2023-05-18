#!/bin/bash

# Check if the test file name is provided
if [[ -z $1 ]]; then
echo "Please provide the test file name as a parameter."
exit 1
fi

# Directory containing the test files
TEST_DIR="test"

# Test file name from the command-line parameter
TEST_FILE_NAME=$1

# Iterate over each subdirectory
for TASK_DIR in "$TEST_DIR"/task*; do
# Construct the path to the test file
TEST_FILE="$TASK_DIR/$TEST_FILE_NAME"

# Check if the test file exists
if [[ -f $TEST_FILE ]]; then
# Run the test using the hsh executable and let it print the output
OUTPUT=$(./test/checker.bash ./hsh "$TEST_FILE")

    # Print the output of the test
        echo "$OUTPUT"

# Check if the output contains "OK" (indicating success)
if [[ "$OUTPUT" == *"OK"* ]]; then
echo -e "\nGreen Check"
fi
fi
done

