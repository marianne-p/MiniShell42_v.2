#!/bin/bash

# The path to your minishell executable
MINISHELL_BIN="./minishell"

# Define some colors for output
GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

# Array of test commands
TEST_COMMANDS=(
  "ls"
  "ls | ls"
  "echo Hello World!"
  "cat src/main.c"
  "echo test && echo another" 
  "ls -a <<infile | cat && echo 'cool'"
)

# Print header
echo "=========================="
echo "      Minishell Tests     "
echo "=========================="

for CMD in "${TEST_COMMANDS[@]}"; do
  echo
  echo "--------------------------"
  echo "Test Command: $CMD"
  echo "--------------------------"

  # 1. Capture output of minishell in non-interactive mode (piping the command)
  OUTPUT=$(echo "$CMD" | $MINISHELL_BIN 2>&1)
  
  # Print the minishell output
  echo "Result:"
  echo "$OUTPUT"

  # 2. Run valgrind on the same scenario
  VALGRIND_OUTPUT=$(echo "$CMD" | valgrind --leak-check=full $MINISHELL_BIN 2>&1)
  
  # Extract lines with 'definitely lost:' and 'ERROR SUMMARY'
  DEFINITELY_LOST=$(echo "$VALGRIND_OUTPUT" | grep "definitely lost:")
  ERROR_SUMMARY=$(echo "$VALGRIND_OUTPUT" | grep "ERROR SUMMARY")

  # Check if "definitely lost:" line is the "0 bytes in 0 blocks" case
  if echo "$DEFINITELY_LOST" | grep -q "definitely lost: 0 bytes in 0 blocks"; then
    echo -e "Valgrind (definitely lost): ${GREEN}$DEFINITELY_LOST${RESET}"
  else
    echo -e "Valgrind (definitely lost): ${RED}$DEFINITELY_LOST${RESET}"
  fi

  # Check if "ERROR SUMMARY" line says "0 errors from 0 contexts (suppressed: 0 from 0)"
  if echo "$ERROR_SUMMARY" | grep -q "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)"; then
    echo -e "Valgrind (error summary):   ${GREEN}$ERROR_SUMMARY${RESET}"
  else
    echo -e "Valgrind (error summary):   ${RED}$ERROR_SUMMARY${RESET}"
  fi

done

echo
echo "All tests completed!"

