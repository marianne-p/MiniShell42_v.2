#!/bin/bash

# The path to your minishell executable
MINISHELL_BIN="./minishell"

# Define some colors for output
GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

# Initialize counters
PASS_COUNT=0
FAIL_COUNT=0

TEST_COMMANDS=(
  "" # 1. Empty input
  "ls" # 2. Single command
  "ls|ls" # 3. Pipe with no space
  "ls | ls" # 4. Pipe with space
  "   echo 'leading spaces test'" # 5. Spaces before command
  "echo 'trailing spaces test'   " # 6. Trailing spaces
  "echo     too     many     spaces" # 7. Multiple spaces between tokens
  "(echo 'no space between tokens')" # 8. Parentheses with no space
  "( echo spaced )" # 9. Parentheses with space
  "echo first && echo second" # 10. Logical AND
  "false || echo 'ran after false'" # 11. Logical OR
  "echo start && false || echo 'fallback'" # 12. Mixed && and ||
  "ls>out.txt" # 13. Redirection with no space
  "ls > out.txt" # 14. Redirection with space
  "echo 'appending'>>out.txt" # 15. Append redirection no space
  "echo 'appending with space' >> out.txt" # 16. Append redirection with space
  "cat <<EOF | grep hello && echo 'Done'" # 17. Here_doc combined with pipe
  "echo \"quoted #comment\" | cat" # 18. Quotes and comments
  "echo '&&' && echo '||'" # 19. Single quotes around logical operators
  "ls | grep src | wc -l" # 20. Multiple pipes in one line
  "(echo << here_doc|cat&&ls)" # 21. Multiple operators without spaces ( (, |, &&, ) )
)

# Print header
echo "=========================="
echo "      Minishell Tests     "
echo "=========================="

i=1

for CMD in "${TEST_COMMANDS[@]}"; do
  echo
  echo "Test $i, Command: $CMD"
  echo "--------------------------"

  #
  # 1. Capture minishell output in non-interactive mode
  #
  OUTPUT=$(echo "$CMD" | $MINISHELL_BIN 2>&1)
  
  # Print the minishell output
  echo "Result:"
  echo "$OUTPUT"

  #
  # 2. Run valgrind on the same scenario
  #
  VALGRIND_OUTPUT=$(echo "$CMD" | valgrind --leak-check=full $MINISHELL_BIN 2>&1)
  
  # Extract lines with 'definitely lost:' and 'ERROR SUMMARY'
  DEFINITELY_LOST=$(echo "$VALGRIND_OUTPUT" | grep "definitely lost:")
  ERROR_SUMMARY=$(echo "$VALGRIND_OUTPUT" | grep "ERROR SUMMARY")

  #
  # 3. Check each line and color-code it
  #
  IS_RED=0
  
  # definitely lost
  if echo "$DEFINITELY_LOST" | grep -q "definitely lost: 0 bytes in 0 blocks"; then
    echo -e "Valgrind (definitely lost): ${GREEN}$DEFINITELY_LOST${RESET}"
  else
    echo -e "Valgrind (definitely lost): ${RED}$DEFINITELY_LOST${RESET}"
    IS_RED=1
  fi

  # error summary
  if echo "$ERROR_SUMMARY" | grep -q "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)"; then
    echo -e "Valgrind (error summary):   ${GREEN}$ERROR_SUMMARY${RESET}"
  else
    echo -e "Valgrind (error summary):   ${RED}$ERROR_SUMMARY${RESET}"
    IS_RED=1
  fi

  #
  # 4. If either line was "red," print the full Valgrind output for debugging
  #
  if [ "$IS_RED" -eq 1 ]; then
    echo -e "${RED}Full Valgrind output (since there's a potential issue):${RESET}"
    echo "$VALGRIND_OUTPUT"
    ((FAIL_COUNT++))
  else
    ((PASS_COUNT++))
  fi
  ((i++))
done

# Print summary
echo
echo "All tests completed!"
echo -e "Passed: ${GREEN}$PASS_COUNT${RESET}"
echo -e "Failed: ${RED}$FAIL_COUNT${RESET}"
