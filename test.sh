#!/bin/bash

# Run the shell in interactive mode
./hsh <<EOF
/bin/ls
exit
EOF

# Run the shell with a command from a file
echo "/bin/ls" | ./hsh

# Run the shell with commands from a file
cat test_ls_2 | ./hsh

