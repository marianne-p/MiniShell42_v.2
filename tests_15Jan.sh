==========================
      Minishell Tests     
==========================

Test 1, Command: 
--------------------------
Result:
 (COMMENT_APPEND)

cmd: ''	
Valgrind (definitely lost): [32m==389135==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389135== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 2, Command: ls
--------------------------
Result:
ls (COMMENT_APPEND)

cmd: 'ls'	
Valgrind (definitely lost): [32m==389151==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389151== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 3, Command: ls|ls
--------------------------
Result:
ls (COMMENT_APPEND) -> | (PIPE) -> ls (COMMENT_APPEND)

cmd: 'ls'	
cmd: 'ls'	
Valgrind (definitely lost): [32m==389167==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389167== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 4, Command: ls | ls
--------------------------
Result:
ls (COMMENT_APPEND) -> | (PIPE) -> ls (COMMENT_APPEND)

cmd: 'ls'	
cmd: 'ls'	
Valgrind (definitely lost): [32m==389183==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389183== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 5, Command:    echo 'leading spaces test'
--------------------------
Result:
echo (COMMENT_APPEND) -> 'leading spaces test' (COMMENT)

cmd: 'echo'	''leading spaces test'' 
Valgrind (definitely lost): [32m==389200==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389200== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 6, Command: echo 'trailing spaces test'   
--------------------------
Result:
echo (COMMENT_APPEND) -> 'trailing spaces test' (COMMENT)

cmd: 'echo'	''trailing spaces test'' 
Valgrind (definitely lost): [32m==389216==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389216== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 7, Command: echo     too     many     spaces
--------------------------
Result:
echo (COMMENT_APPEND) -> too (COMMENT_APPEND) -> many (COMMENT_APPEND) -> spaces (COMMENT_APPEND)

cmd: 'echo'	'too' 'many' 'spaces' 
Valgrind (definitely lost): [32m==389232==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389232== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 8, Command: ls>out.txt
--------------------------
Result:
ls>out.txt (COMMENT_APPEND)

cmd: 'ls>out.txt'	
Valgrind (definitely lost): [32m==389248==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389248== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 9, Command: ls > out.txt
--------------------------
Result:
ls (COMMENT_APPEND) -> out.txt (OUT_REDIR)

cmd: 'ls'	
		outred: 'out.txt' 
Valgrind (definitely lost): [32m==389264==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389264== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 10, Command: echo 'appending'>>out.txt
--------------------------
Result:
echo (COMMENT_APPEND) -> 'appending'>>out.txt (COMMENT)

cmd: 'echo'	''appending'>>out.txt' 
Valgrind (definitely lost): [32m==389280==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389280== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 11, Command: echo 'appending with space' >> out.txt
--------------------------
Result:
echo (COMMENT_APPEND) -> 'appending with space' (COMMENT) -> out.txt (OUT_REDIR_APPEND)

cmd: 'echo'	''appending with space'' 
		outred: 'out.txt' 
Valgrind (definitely lost): [32m==389296==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389296== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 12, Command: cat <<EOF | grep hello && echo 'Done'
--------------------------
Result:
cat (COMMENT_APPEND) -> EOF (HERE_DOC) -> | (PIPE) -> grep (COMMENT_APPEND) -> hello (COMMENT_APPEND) -> && (AND) -> echo (COMMENT_APPEND) -> 'Done' (COMMENT)

cmd: 'cat'	
		inred: 'EOF' 
cmd: 'grep'	'hello' '&&' 'echo' ''Done'' 
Valgrind (definitely lost): [32m==389312==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389312== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 13, Command: echo "quoted #comment" | cat
--------------------------
Result:
echo (COMMENT_APPEND) -> "quoted #comment" (COMMENT_APPEND) -> | (PIPE) -> cat (COMMENT_APPEND)

cmd: 'echo'	'"quoted #comment"' 
cmd: 'cat'	
Valgrind (definitely lost): [32m==389328==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389328== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 14, Command: ls | grep src | wc -l
--------------------------
Result:
ls (COMMENT_APPEND) -> | (PIPE) -> grep (COMMENT_APPEND) -> src (COMMENT_APPEND) -> | (PIPE) -> wc (COMMENT_APPEND) -> -l (COMMENT_APPEND)

cmd: 'ls'	
cmd: 'grep'	'src' 
cmd: 'wc'	'-l' 
Valgrind (definitely lost): [32m==389344==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389344== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 15, Command: grep 'pattern' < in.txt
--------------------------
Result:
grep (COMMENT_APPEND) -> 'pattern' (COMMENT) -> in.txt (IN_REDIR)

cmd: 'grep'	''pattern'' 
		inred: 'in.txt' 
Valgrind (definitely lost): [32m==389360==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389360== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 16, Command: grep 'pattern' < in.txt > out.txt
--------------------------
Result:
grep (COMMENT_APPEND) -> 'pattern' (COMMENT) -> in.txt (IN_REDIR) -> out.txt (OUT_REDIR)

cmd: 'grep'	''pattern'' 
		inred: 'in.txt' 
		outred: 'out.txt' 
Valgrind (definitely lost): [32m==389376==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389376== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 17, Command: grep 'pattern' < in.txt >> out.txt
--------------------------
Result:
grep (COMMENT_APPEND) -> 'pattern' (COMMENT) -> in.txt (IN_REDIR) -> out.txt (OUT_REDIR_APPEND)

cmd: 'grep'	''pattern'' 
		inred: 'in.txt' 
		outred: 'out.txt' 
Valgrind (definitely lost): [32m==389392==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389392== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 18, Command: echo "double quotes with spaces" | wc -w
--------------------------
Result:
echo (COMMENT_APPEND) -> "double quotes with spaces" (COMMENT_APPEND) -> | (PIPE) -> wc (COMMENT_APPEND) -> -w (COMMENT_APPEND)

cmd: 'echo'	'"double quotes with spaces"' 
cmd: 'wc'	'-w' 
Valgrind (definitely lost): [32m==389408==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389408== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 19, Command: echo 'single quotes with spaces' | wc -w
--------------------------
Result:
echo (COMMENT_APPEND) -> 'single quotes with spaces' (COMMENT) -> | (PIPE) -> wc (COMMENT_APPEND) -> -w (COMMENT_APPEND)

cmd: 'echo'	''single quotes with spaces'' 
cmd: 'wc'	'-w' 
Valgrind (definitely lost): [32m==389424==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389424== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 20, Command: cat <<EOF | grep 'invalid
--------------------------
Result:
cat (COMMENT_APPEND) -> EOF (HERE_DOC) -> | (PIPE) -> grep (COMMENT_APPEND) -> 'invalid
 (COMMENT)

cmd: 'cat'	
		inred: 'EOF' 
cmd: 'grep'	''invalid
' 
Valgrind (definitely lost): [32m==389440==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [31m==389440== ERROR SUMMARY: 4193235 errors from 2 contexts (suppressed: 0 from 0)[0m
[31mFull Valgrind output (since there's a potential issue):[0m
==389440== Memcheck, a memory error detector
==389440== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==389440== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==389440== Command: ./minishell
==389440== 
==389440== Invalid read of size 1
==389440==    at 0x402599: copy_token (token_split_logical.c:89)
==389440==    by 0x402E0B: create_outred_struct (token_split_logical.c:219)
==389440==    by 0x402F37: create_string_struct (token_split_logical.c:239)
==389440==    by 0x403031: split_logical (token_split_logical.c:254)
==389440==    by 0x4018D0: tokenize (token.c:31)
==389440==    by 0x40198C: tokenize_oneline (token.c:61)
==389440==    by 0x401591: handle_oneline (main.c:88)
==389440==    by 0x40182A: main (main.c:159)
==389440==  Address 0x4b223ab is 0 bytes after a block of size 27 alloc'd
==389440==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==389440==    by 0x4057B9: ft_strdup (in /home/mpihur/25Jan/MiniShell42_v.2/minishell)
==389440==    by 0x401884: tokenize (token.c:24)
==389440==    by 0x40198C: tokenize_oneline (token.c:61)
==389440==    by 0x401591: handle_oneline (main.c:88)
==389440==    by 0x40182A: main (main.c:159)
==389440== 
==389440== Conditional jump or move depends on uninitialised value(s)
==389440==    at 0x4025A0: copy_token (token_split_logical.c:89)
==389440==    by 0x402E0B: create_outred_struct (token_split_logical.c:219)
==389440==    by 0x402F37: create_string_struct (token_split_logical.c:239)
==389440==    by 0x403031: split_logical (token_split_logical.c:254)
==389440==    by 0x4018D0: tokenize (token.c:31)
==389440==    by 0x40198C: tokenize_oneline (token.c:61)
==389440==    by 0x401591: handle_oneline (main.c:88)
==389440==    by 0x40182A: main (main.c:159)
==389440== 
==389440== 
==389440== Process terminating with default action of signal 11 (SIGSEGV)
==389440==  Access not within mapped region at address 0x4F22000
==389440==    at 0x402599: copy_token (token_split_logical.c:89)
==389440==    by 0x402E0B: create_outred_struct (token_split_logical.c:219)
==389440==    by 0x402F37: create_string_struct (token_split_logical.c:239)
==389440==    by 0x403031: split_logical (token_split_logical.c:254)
==389440==    by 0x4018D0: tokenize (token.c:31)
==389440==    by 0x40198C: tokenize_oneline (token.c:61)
==389440==    by 0x401591: handle_oneline (main.c:88)
==389440==    by 0x40182A: main (main.c:159)
==389440==  If you believe this happened as a result of a stack
==389440==  overflow in your program's main thread (unlikely but
==389440==  possible), you can try to increase the size of the
==389440==  main thread stack using the --main-stacksize= flag.
==389440==  The main thread stack size used in this run was 8388608.
==389440== 
==389440== HEAP SUMMARY:
==389440==     in use at exit: 261 bytes in 12 blocks
==389440==   total heap usage: 19 allocs, 7 frees, 384 bytes allocated
==389440== 
==389440== LEAK SUMMARY:
==389440==    definitely lost: 0 bytes in 0 blocks
==389440==    indirectly lost: 0 bytes in 0 blocks
==389440==      possibly lost: 0 bytes in 0 blocks
==389440==    still reachable: 261 bytes in 12 blocks
==389440==         suppressed: 0 bytes in 0 blocks
==389440== Reachable blocks (those to which a pointer was found) are not shown.
==389440== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==389440== 
==389440== Use --track-origins=yes to see where uninitialised values come from
==389440== For lists of detected and suppressed errors, rerun with: -s
==389440== ERROR SUMMARY: 4193235 errors from 2 contexts (suppressed: 0 from 0)

Test 21, Command: ls | | wc -l
--------------------------
Result:
ls (COMMENT_APPEND) -> | (PIPE) -> | (PIPE) -> wc (COMMENT_APPEND) -> -l (COMMENT_APPEND)

cmd: 'ls'	
cmd: '(null)'	
cmd: 'wc'	'-l' 
Valgrind (definitely lost): [32m==389463==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [31m==389463== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)[0m
[31mFull Valgrind output (since there's a potential issue):[0m
==389463== Memcheck, a memory error detector
==389463== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==389463== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==389463== Command: ./minishell
==389463== 
ls (COMMENT_APPEND) -> | (PIPE) -> | (PIPE) -> wc (COMMENT_APPEND) -> -l (COMMENT_APPEND)

cmd: 'ls'	
cmd: '(null)'	==389463== Invalid read of size 8
==389463==    at 0x404516: print_parsed (parse.c:51)
==389463==    by 0x404782: parse (parse.c:103)
==389463==    by 0x4015CF: handle_oneline (main.c:91)
==389463==    by 0x40182A: main (main.c:159)
==389463==  Address 0x4b228a8 is 0 bytes after a block of size 8 alloc'd
==389463==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==389463==    by 0x40471D: parse (parse.c:93)
==389463==    by 0x4015CF: handle_oneline (main.c:91)
==389463==    by 0x40182A: main (main.c:159)
==389463== 

cmd: 'wc'	'-l' ==389463== 
==389463== HEAP SUMMARY:
==389463==     in use at exit: 32 bytes in 1 blocks
==389463==   total heap usage: 29 allocs, 28 frees, 531 bytes allocated
==389463== 
==389463== LEAK SUMMARY:
==389463==    definitely lost: 0 bytes in 0 blocks
==389463==    indirectly lost: 0 bytes in 0 blocks
==389463==      possibly lost: 0 bytes in 0 blocks
==389463==    still reachable: 32 bytes in 1 blocks
==389463==         suppressed: 0 bytes in 0 blocks
==389463== Reachable blocks (those to which a pointer was found) are not shown.
==389463== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==389463== 
==389463== For lists of detected and suppressed errors, rerun with: -s
==389463== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

Test 22, Command: >> out.txt echo invalid
--------------------------
Result:
out.txt (OUT_REDIR_APPEND) -> echo (COMMENT_APPEND) -> invalid (COMMENT_APPEND)

cmd: 'echo'	'invalid' 
		outred: 'out.txt' 
Valgrind (definitely lost): [32m==389479==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389479== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 23, Command: | ls
--------------------------
Result:
| (PIPE) -> ls (COMMENT_APPEND)

cmd: '(null)'	
cmd: 'ls'	
Valgrind (definitely lost): [32m==389495==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [31m==389495== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)[0m
[31mFull Valgrind output (since there's a potential issue):[0m
==389495== Memcheck, a memory error detector
==389495== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==389495== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==389495== Command: ./minishell
==389495== 
| (PIPE) -> ls (COMMENT_APPEND)

cmd: '(null)'	==389495== Invalid read of size 8
==389495==    at 0x404516: print_parsed (parse.c:51)
==389495==    by 0x404782: parse (parse.c:103)
==389495==    by 0x4015CF: handle_oneline (main.c:91)
==389495==    by 0x40182A: main (main.c:159)
==389495==  Address 0x4b22588 is 0 bytes after a block of size 8 alloc'd
==389495==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==389495==    by 0x40471D: parse (parse.c:93)
==389495==    by 0x4015CF: handle_oneline (main.c:91)
==389495==    by 0x40182A: main (main.c:159)
==389495== 

cmd: 'ls'	==389495== 
==389495== HEAP SUMMARY:
==389495==     in use at exit: 32 bytes in 1 blocks
==389495==   total heap usage: 19 allocs, 18 frees, 317 bytes allocated
==389495== 
==389495== LEAK SUMMARY:
==389495==    definitely lost: 0 bytes in 0 blocks
==389495==    indirectly lost: 0 bytes in 0 blocks
==389495==      possibly lost: 0 bytes in 0 blocks
==389495==    still reachable: 32 bytes in 1 blocks
==389495==         suppressed: 0 bytes in 0 blocks
==389495== Reachable blocks (those to which a pointer was found) are not shown.
==389495== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==389495== 
==389495== For lists of detected and suppressed errors, rerun with: -s
==389495== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

Test 24, Command: ls |
--------------------------
Result:
ls (COMMENT_APPEND) -> | (PIPE)
Valgrind (definitely lost): [32m==389512==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [31m==389512== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)[0m
[31mFull Valgrind output (since there's a potential issue):[0m
==389512== Memcheck, a memory error detector
==389512== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==389512== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==389512== Command: ./minishell
==389512== 
ls (COMMENT_APPEND) -> | (PIPE)
==389512== Invalid read of size 4
==389512==    at 0x404679: parse (parse.c:83)
==389512==    by 0x4015CF: handle_oneline (main.c:91)
==389512==    by 0x40182A: main (main.c:159)
==389512==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==389512== 
==389512== 
==389512== Process terminating with default action of signal 11 (SIGSEGV)
==389512==  Access not within mapped region at address 0x0
==389512==    at 0x404679: parse (parse.c:83)
==389512==    by 0x4015CF: handle_oneline (main.c:91)
==389512==    by 0x40182A: main (main.c:159)
==389512==  If you believe this happened as a result of a stack
==389512==  overflow in your program's main thread (unlikely but
==389512==  possible), you can try to increase the size of the
==389512==  main thread stack using the --main-stacksize= flag.
==389512==  The main thread stack size used in this run was 8388608.
==389512== 
==389512== HEAP SUMMARY:
==389512==     in use at exit: 224 bytes in 10 blocks
==389512==   total heap usage: 19 allocs, 9 frees, 317 bytes allocated
==389512== 
==389512== LEAK SUMMARY:
==389512==    definitely lost: 0 bytes in 0 blocks
==389512==    indirectly lost: 0 bytes in 0 blocks
==389512==      possibly lost: 0 bytes in 0 blocks
==389512==    still reachable: 224 bytes in 10 blocks
==389512==         suppressed: 0 bytes in 0 blocks
==389512== Reachable blocks (those to which a pointer was found) are not shown.
==389512== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==389512== 
==389512== For lists of detected and suppressed errors, rerun with: -s
==389512== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

Test 25, Command: ls >>
--------------------------
Result:
ls (COMMENT_APPEND) ->  (OUT_REDIR_APPEND)

cmd: 'ls'	
		outred: '' 
Valgrind (definitely lost): [32m==389533==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389533== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 26, Command: cat <<EOF && echo done
--------------------------
Result:
cat (COMMENT_APPEND) -> EOF (HERE_DOC) -> && (AND) -> echo (COMMENT_APPEND) -> done (COMMENT_APPEND)

cmd: 'cat'	'&&' 'echo' 'done' 
		inred: 'EOF' 
Valgrind (definitely lost): [32m==389549==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389549== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 27, Command: echo "quotes within \"quotes\""
--------------------------
Result:
echo (COMMENT_APPEND) -> "quotes within \"quotes\"" (COMMENT_APPEND)

cmd: 'echo'	'"quotes within \"quotes\""' 
Valgrind (definitely lost): [32m==389565==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==389565== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

All tests completed!
Passed: [32m23[0m
Failed: [31m4[0m
