==========================
      Minishell Tests     
==========================

Test 1, Command: 
--------------------------
Result:
 (COMMENT_APPEND)

cmd: ''	
Valgrind (definitely lost): [32m==114655==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114655== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 2, Command: ls
--------------------------
Result:
ls (COMMENT_APPEND)

cmd: 'ls'	
Valgrind (definitely lost): [32m==114675==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114675== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 3, Command: ls|ls
--------------------------
Result:
ls (COMMENT_APPEND) -> | (PIPE) -> ls (COMMENT_APPEND)

cmd: 'ls'	
cmd: 'ls'	
Valgrind (definitely lost): [32m==114695==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114695== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 4, Command: ls | ls
--------------------------
Result:
ls (COMMENT_APPEND) -> | (PIPE) -> ls (COMMENT_APPEND)

cmd: 'ls'	
cmd: 'ls'	
Valgrind (definitely lost): [32m==114715==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114715== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 5, Command:    echo 'leading spaces test'
--------------------------
Result:
echo (COMMENT_APPEND) -> 'leading spaces test' (COMMENT)

cmd: 'echo'	''leading spaces test'' 
Valgrind (definitely lost): [32m==114735==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114735== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 6, Command: echo 'trailing spaces test'   
--------------------------
Result:
echo (COMMENT_APPEND) -> 'trailing spaces test' (COMMENT)

cmd: 'echo'	''trailing spaces test'' 
Valgrind (definitely lost): [32m==114755==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114755== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 7, Command: echo     too     many     spaces
--------------------------
Result:
echo (COMMENT_APPEND) -> too (COMMENT_APPEND) -> many (COMMENT_APPEND) -> spaces (COMMENT_APPEND)

cmd: 'echo'	'too' 'many' 'spaces' 
Valgrind (definitely lost): [32m==114775==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114775== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 8, Command: ls>out.txt
--------------------------
Result:
ls>out.txt (COMMENT_APPEND)

cmd: 'ls>out.txt'	
Valgrind (definitely lost): [32m==114795==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114795== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 9, Command: ls > out.txt
--------------------------
Result:
ls (COMMENT_APPEND) -> out.txt (OUT_REDIR)

cmd: 'ls'	
		outred: 'out.txt' 
Valgrind (definitely lost): [32m==114815==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114815== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 10, Command: echo 'appending'>>out.txt
--------------------------
Result:
echo (COMMENT_APPEND) -> 'appending'>>out.txt (COMMENT)

cmd: 'echo'	''appending'>>out.txt' 
Valgrind (definitely lost): [32m==114836==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114836== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 11, Command: echo 'appending with space' >> out.txt
--------------------------
Result:
echo (COMMENT_APPEND) -> 'appending with space' (COMMENT) -> out.txt (OUT_REDIR_APPEND)

cmd: 'echo'	''appending with space'' 
		outred: 'out.txt' 
Valgrind (definitely lost): [32m==114856==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114856== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 12, Command: cat <<EOF | grep hello && echo 'Done'
--------------------------
Result:
cat (COMMENT_APPEND) -> EOF (HERE_DOC) -> | (PIPE) -> grep (COMMENT_APPEND) -> hello (COMMENT_APPEND) -> && (AND) -> echo (COMMENT_APPEND) -> 'Done' (COMMENT)

cmd: 'cat'	
		inred: 'EOF' 
cmd: 'grep'	'hello' '&&' 'echo' ''Done'' 
Valgrind (definitely lost): [32m==114876==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114876== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 13, Command: echo "quoted #comment" | cat
--------------------------
Result:
echo (COMMENT_APPEND) -> "quoted #comment" (COMMENT_APPEND) -> | (PIPE) -> cat (COMMENT_APPEND)

cmd: 'echo'	'"quoted #comment"' 
cmd: 'cat'	
Valgrind (definitely lost): [32m==114896==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114896== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 14, Command: ls | grep src | wc -l
--------------------------
Result:
ls (COMMENT_APPEND) -> | (PIPE) -> grep (COMMENT_APPEND) -> src (COMMENT_APPEND) -> | (PIPE) -> wc (COMMENT_APPEND) -> -l (COMMENT_APPEND)

cmd: 'ls'	
cmd: 'grep'	'src' 
cmd: 'wc'	'-l' 
Valgrind (definitely lost): [32m==114916==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114916== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 15, Command: grep 'pattern' < in.txt
--------------------------
Result:
grep (COMMENT_APPEND) -> 'pattern' (COMMENT) -> in.txt (IN_REDIR)

cmd: 'grep'	''pattern'' 
		inred: 'in.txt' 
Valgrind (definitely lost): [32m==114936==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114936== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 16, Command: grep 'pattern' < in.txt > out.txt
--------------------------
Result:
grep (COMMENT_APPEND) -> 'pattern' (COMMENT) -> in.txt (IN_REDIR) -> out.txt (OUT_REDIR)

cmd: 'grep'	''pattern'' 
		inred: 'in.txt' 
		outred: 'out.txt' 
Valgrind (definitely lost): [32m==114956==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114956== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 17, Command: grep 'pattern' < in.txt >> out.txt
--------------------------
Result:
grep (COMMENT_APPEND) -> 'pattern' (COMMENT) -> in.txt (IN_REDIR) -> out.txt (OUT_REDIR_APPEND)

cmd: 'grep'	''pattern'' 
		inred: 'in.txt' 
		outred: 'out.txt' 
Valgrind (definitely lost): [32m==114976==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114976== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 18, Command: echo "double quotes with spaces" | wc -w
--------------------------
Result:
echo (COMMENT_APPEND) -> "double quotes with spaces" (COMMENT_APPEND) -> | (PIPE) -> wc (COMMENT_APPEND) -> -w (COMMENT_APPEND)

cmd: 'echo'	'"double quotes with spaces"' 
cmd: 'wc'	'-w' 
Valgrind (definitely lost): [32m==114996==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==114996== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 19, Command: echo 'single quotes with spaces' | wc -w
--------------------------
Result:
echo (COMMENT_APPEND) -> 'single quotes with spaces' (COMMENT) -> | (PIPE) -> wc (COMMENT_APPEND) -> -w (COMMENT_APPEND)

cmd: 'echo'	''single quotes with spaces'' 
cmd: 'wc'	'-w' 
Valgrind (definitely lost): [32m==115016==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==115016== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 20, Command: cat <<EOF | grep 'invalid
--------------------------
Result:
The matching quote (') is missing
Valgrind (definitely lost): [31m[0m
Valgrind (error summary):   [32m==115036== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m
[31mLogical/Parsing error, but memory is clean.[0m

Test 21, Command: ls | | wc -l
--------------------------
Result:
ls (COMMENT_APPEND) -> | (PIPE) -> | (PIPE) -> wc (COMMENT_APPEND) -> -l (COMMENT_APPEND)
Wrong pipe/cmd pattern
Valgrind (definitely lost): [31m[0m
Valgrind (error summary):   [32m==115055== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m
[31mLogical/Parsing error, but memory is clean.[0m

Test 22, Command: >> out.txt echo invalid
--------------------------
Result:
out.txt (OUT_REDIR_APPEND) -> echo (COMMENT_APPEND) -> invalid (COMMENT_APPEND)

cmd: 'echo'	'invalid' 
		outred: 'out.txt' 
Valgrind (definitely lost): [32m==115074==    definitely lost: 0 bytes in 0 blocks[0m
Valgrind (error summary):   [32m==115074== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m

Test 23, Command: | ls
--------------------------
Result:
| (PIPE) -> ls (COMMENT_APPEND)
Wrong pipe/cmd pattern
Valgrind (definitely lost): [31m[0m
Valgrind (error summary):   [32m==115095== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m
[31mLogical/Parsing error, but memory is clean.[0m

Test 24, Command: ls |
--------------------------
Result:
ls (COMMENT_APPEND) -> | (PIPE)
Wrong pipe/cmd number
Valgrind (definitely lost): [31m[0m
Valgrind (error summary):   [32m==115114== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)[0m
[31mLogical/Parsing error, but memory is clean.[0m

Test 25, Command: ls >>
--------------------------
Result:
ls (COMMENT_APPEND) ->  (OUT_REDIR_APPEND)

cmd: 'ls'	
		outred: '' 
