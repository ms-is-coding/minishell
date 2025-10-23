#!/bin/bash

# ===============================
# Colors
# ===============================
RED=$'\033[0;31m'
GREEN=$'\033[0;32m'
YELLOW=$'\033[1;33m'
BLUE=$'\033[0;34m'
CYAN=$'\033[0;36m'
BOLD=$'\033[1m'
RESET=$'\033[0m'

# ===============================
# Counters
# ===============================
TOTAL=0
PASSED=0
FAILED=0
VERBOSE=0

[[ "$1" == "--verbose" ]] && VERBOSE=1

# ===============================
# UI Helpers
# ===============================
hr() { echo $BLUE$BOLD$'\n'"━━━━━━━━━━━━━ $1 ━━━━━━━━━━━━━"$RESET; }

print_header() {
	echo $CYAN"╭──────────────────────╮"$RESET
	echo $CYAN"│   POSIX SHELL TESTER │"$RESET
	echo $CYAN"╰──────────────────────╯"$RESET
	echo ""
}

summary() {
	echo ""
	echo $CYAN"╭───────────────╮"$RESET
	echo $CYAN"│    RESULTS    │"$RESET
	echo $CYAN"├───────────────┤"$RESET
	printf $CYAN"│ "$RESET$BLUE"Total:%7d "$RESET$CYAN"│\n"$RESET $TOTAL
	printf $CYAN"│ "$RESET$GREEN"Success:%5d "$RESET$CYAN"│\n"$RESET $PASSED
	printf $CYAN"│ "$RESET$RED"Failure:%5d "$RESET$CYAN"│\n"$RESET $FAILED
	if [ $TOTAL -gt 0 ]; then
		PERCENT=$((PASSED * 100 / TOTAL))
		printf $CYAN"│ "$RESET"Score:%6d%% "$CYAN"│\n"$RESET $PERCENT
	fi
	echo $CYAN"╰───────────────╯"$RESET
	[ $FAILED -eq 0 ] && echo $GREEN$BOLD"\n[PASS] All tests passed"$RESET || echo $RED$BOLD$'\n'"[FAIL] Some tests failed"$RESET
}

# ===============================
# Core test logic
# ===============================
test_cmd() {
	local name="$1"
	local cmd="$2"
	TOTAL=$((TOTAL + 1))

	timeout 3s ./minishell -c "$cmd" 1>/tmp/msh_out 2>/tmp/msh_err
	local mshexit=$?
	timeout 3s bash --posix -c "$cmd" 1>/tmp/bash_out 2>/tmp/bash_err
	local bashexit=$?

	if [ "$mshexit" -ne "$bashexit" ]; then
		echo -e "$RED[FAIL]$RESET $name (exit: $mshexit ≠ $bashexit)"
		((FAILED++))
	elif ! diff -q /tmp/msh_out /tmp/bash_out >/dev/null; then
		echo -e "$RED[FAIL]$RESET $name (stdout mismatch)"
		((FAILED++))
		[ $VERBOSE -eq 1 ] && diff --side-by-side /tmp/bash_out /tmp/msh_out | head -n 10
	elif ! diff -q /tmp/msh_err /tmp/bash_err >/dev/null; then
		echo -e "$YELLOW[WARN]$RESET $name (stderr mismatch)"
		((PASSED++))
		[ $VERBOSE -eq 1 ] && diff --side-by-side /tmp/bash_err /tmp/msh_err | head -n 5
	else
		echo -e "$GREEN[PASS]$RESET $name"
		((PASSED++))
	fi
}

# ===============================
# Test definitions
# ===============================
setup_test_files() {
	mkdir -p /tmp/test_dir
	echo "foo bar" > /tmp/test.txt
	echo "a\nb\nc" > /tmp/input.txt
	touch /tmp/test_dir/file1 /tmp/test_dir/file2.txt
}

run_tests() {
	# ============================================================================
	# MINISHELL SUBJECT TESTS (MANDATORY)
	# ============================================================================
	hr "Builtins"

	test_cmd "echo simple" "echo Hello World"
	test_cmd "echo multiple args" "echo one two three"
	test_cmd "echo -n" "echo -n test"
	test_cmd "echo empty" "echo"
	test_cmd "echo spaces" "echo    multiple    spaces"

	test_cmd "pwd basic" "pwd"
	test_cmd "pwd extra arg" "pwd test"

	test_cmd "cd no args" "cd"
	test_cmd "cd /tmp" "cd /tmp && pwd"
	test_cmd "cd relative" "mkdir -p /tmp/test_cd && cd /tmp/test_cd && pwd"
	test_cmd "cd invalid" "cd /no/such/path"
	test_cmd "cd -" "cd /tmp && cd - >/dev/null && pwd"
	test_cmd "cd /./////.///////.//" "cd /./////.///////.//; pwd"
	test_cmd "cd magic" "mkdir -p a/b; cd a/b; pwd; rm -r ../../a; cd ../..; pwd"

	test_cmd "export new var" "export FOO=bar && echo \$FOO"
	test_cmd "export modify var" "export FOO=bar && export FOO=baz && echo \$FOO"
	test_cmd "export no value" "export VAR && env | grep VAR"
	test_cmd "export invalid" "export 123=abc"
	test_cmd "export list" "export | sort | head -n 3"

	test_cmd "unset existing" "export TMP=1 && unset TMP && echo \$TMP"
	test_cmd "unset nonexistent" "unset NONEXISTENT"
	test_cmd "unset multiple" "export A=1 B=2 && unset A B && env | sort | grep -E 'A|B'"

	test_cmd "env basic" "env | grep PWD"
	test_cmd "env sorted" "env | sort | head -n 5"
	test_cmd "env with arg" "env foo"

	test_cmd "exit 0" "exit 0"
	test_cmd "exit 42" "exit 42"
	test_cmd "exit invalid" "exit abc"
	test_cmd "exit too many args" "exit 1 2"
	test_cmd "exit with code" "false; exit"

	# ============================================================================
	hr "Environment variables"

	test_cmd "\$PATH exists" "echo \$PATH"
	test_cmd "\$HOME exists" "echo \$HOME"
	test_cmd "\$USER exists" "echo \$USER"
	test_cmd "undefined var" "echo \$NONEXISTENT"
	test_cmd "set and echo" "export TEST=ok && echo \$TEST"
	test_cmd "reassign var" "export TEST=1 && export TEST=2 && echo \$TEST"
	test_cmd "exit code success" "true && echo \$?"
	test_cmd "exit code failure" "false || echo \$?"
	test_cmd "quoted expansion" "echo \"value:\$PATH\""

	# ============================================================================
	hr "Quotes and Escapes"

	test_cmd "single quotes" "echo 'hello world'"
	test_cmd "double quotes" "echo \"hello world\""
	test_cmd "mixed quotes" "echo 'a'\"b\"'c'"
	test_cmd "empty quotes" "echo ''"
	test_cmd "escaped quotes" "echo \"He said \\\"hi\\\"\""
	test_cmd "literal \$ inside single" "echo '\$PATH'"
	test_cmd "expanded \$ inside double" "echo \"\$PATH\""
	test_cmd "backslash in double" "echo \"a\\b\""
	test_cmd "backslash outside" "echo a\\ b"

	# ============================================================================
	hr "Redirections"

	test_cmd "redir output >" "echo test > /tmp/redir1.txt && cat /tmp/redir1.txt"
	test_cmd "redir append >>" "echo 1 > /tmp/redir2.txt && echo 2 >> /tmp/redir2.txt && cat /tmp/redir2.txt"
	test_cmd "redir input <" "cat < /tmp/redir1.txt"
	test_cmd "redir overwrite chain" "echo a > /tmp/a && echo b > /tmp/a && cat /tmp/a"
	test_cmd "redir error" "cat < /no/such/file"
	test_cmd "multiple redirs" "echo hi > /tmp/a > /tmp/b && cat /tmp/b"
	test_cmd "heredoc simple" "cat <<EOF
one
two
EOF"
	test_cmd "heredoc with expansion" "cat <<EOF
\$HOME
EOF"
	test_cmd "redir to directory" "echo test > /tmp"

	# ============================================================================
	hr "Pipes"

	test_cmd "single pipe" "echo hi | cat"
	test_cmd "double pipe" "echo hi | cat | cat"
	test_cmd "pipe grep" "echo hello world | grep hello"
	test_cmd "pipe wc" "echo -e 'a\nb\nc' | wc -l"
	test_cmd "pipe and redir" "echo hi | cat > /tmp/piperes.txt && cat /tmp/piperes.txt"
	test_cmd "pipe stderr" "ls /no/such | cat"
	test_cmd "pipe with empty" "echo hi | | cat"
	test_cmd "nested pipes" "echo a | (cat | (cat | cat))"

	# ============================================================================
	hr "Logical operators"

	test_cmd "and success" "true && echo ok"
	test_cmd "and failure" "false && echo no"
	test_cmd "or success" "false || echo ok"
	test_cmd "or failure" "true || echo no"
	test_cmd "and/or chain" "true && false || echo recovered"
	test_cmd "mix with pipes" "false && echo nope | echo done"

	# ============================================================================
	hr "Parentheses / Subshells"

	test_cmd "simple subshell" "(echo hi)"
	test_cmd "pipe in subshell" "(echo hi | tr a-z A-Z)"
	test_cmd "redir in subshell" "(echo x > /tmp/sub.txt)"
	test_cmd "nested subshells" "\(\(echo hi))"
	test_cmd "subshell and export" "(export A=5; echo \$A)"
	test_cmd "group command" "{ echo group; echo block; }"
	test_cmd "redir group" "{ echo A; echo B; } > /tmp/group.txt && cat /tmp/group.txt"

	# ============================================================================
	hr "Wildcards"

	test_cmd "simple glob" "echo /tmp/*"
	test_cmd "txt glob" "echo /tmp/*.txt"
	test_cmd "no matches" "echo *.nomatch"
	test_cmd "nested glob" "mkdir -p /tmp/a/b; touch /tmp/a/b/f; echo /tmp/a/*/*"
	test_cmd "mixed text and glob" "echo x*/t*"

	# ============================================================================
	hr "Syntax errors"

	test_cmd "pipe at start" "| echo hi"
	test_cmd "pipe at end" "echo hi |"
	test_cmd "redir without file" "echo hi >"
	test_cmd "unterminated quote" "echo 'hi"
	test_cmd "bad logical op" "echo hi &&&& echo no"
	test_cmd "bad syntax semicolon" "echo hi ;; echo bye"
	test_cmd "newline escape" "echo hi \\"

	# ============================================================================
	hr "Bonus Features"

	test_cmd "logical &&" "true && echo success"
	test_cmd "logical ||" "false || echo fallback"
	test_cmd "pipe + logic" "echo hi | cat && echo ok"
	test_cmd "parentheses + logic" "(echo a && echo b) || echo c"
	test_cmd "subshell in pipe" "(echo hello | tr a-z A-Z) | cat"

	# ============================================================================
	# EXTENDED POSIX TEST SUITE
	# ============================================================================
	hr "Arithmetic expansion"

	test_cmd "basic arithmetic" "echo \$((1+2))"
	test_cmd "precedence" "echo \$((2+3*4))"
	test_cmd "nested arithmetic" "echo \$(( (2+3)*4 ))"
	test_cmd "invalid arithmetic" "echo \$((1+/2))"
	test_cmd "arithmetic var" "x=5; echo \$((x*2))"

	# ============================================================================
	hr "Parameter expansion"

	test_cmd "default value" "unset VAR; echo \${VAR:-fallback}"
	test_cmd "assign default" "unset VAR; echo \${VAR:=newval}; echo \$VAR"
	test_cmd "alternate value" "VAR=1; echo \${VAR:+alt}"
	test_cmd "unset length" "unset VAR; echo \${#VAR}"
	test_cmd "length of var" "A=abcdef; echo \${#A}"
	test_cmd "substring" "A=abcdef; echo \${A:2:3}"
	test_cmd "remove prefix" "A=foo.txt; echo \${A%.txt}"
	test_cmd "remove suffix" "A=dir/file.c; echo \${A##*/}"

	# ============================================================================
	hr "Command substitution"

	test_cmd "simple sub" "echo \$(echo hi)"
	test_cmd "nested sub" "echo \$(echo \$(echo deep))"
	test_cmd "redir in sub" "echo \$(echo test > /tmp/subredir.txt; cat /tmp/subredir.txt)"
	test_cmd "exit in sub" "echo \$(exit 5)"
	test_cmd "sub in quotes" "echo \"result=\$(echo 5)\""

	# ============================================================================
	hr "Loops"

	test_cmd "for loop" "for i in 1 2 3; do echo \$i; done"
	test_cmd "while loop" "i=0; while [ \$i -lt 3 ]; do echo \$i; i=\$((i+1)); done"
	test_cmd "until loop" "i=0; until [ \$i -gt 2 ]; do echo \$i; i=\$((i+1)); done"
	test_cmd "break continue" "for i in 1 2 3; do [ \$i -eq 2 ] && break; echo \$i; done"
	test_cmd "nested loops" "for a in x y; do for b in 1 2; do echo \$a\$b; done; done"

	# ============================================================================
	hr "Conditionals"

	test_cmd "if then else" "if true; then echo ok; else echo fail; fi"
	test_cmd "elif chain" "if false; then echo no; elif true; then echo yes; fi"
	test_cmd "test builtin" "type test; [ -f /tmp/redir1.txt ] && echo file"
	test_cmd "negation" "if ! false; then echo ok; fi"
	test_cmd "arithmetic test" "[ \$((1+1)) -eq 2 ] && echo math"

	# ============================================================================
	hr "Functions"

	test_cmd "define and call" "f(){ echo hi; }; f"
	test_cmd "return status" "f(){ return 7; }; f; echo \$?"
	test_cmd "local vars" "f(){ local x=5; echo \$x; }; f"
	test_cmd "recursive" "f(){ [ \$1 -eq 0 ] && return; echo \$1; f \$((\$1-1));}; f 3"
	test_cmd "function export" "f(){ echo hi; }; export -f f; bash -c f"

	# ============================================================================
	hr "Job control (optional)"

	test_cmd "background job" "sleep 0.1 & echo done"
	test_cmd "multiple jobs" "sleep 0.1 & sleep 0.2 & echo ok"
	test_cmd "fg builtin" "sleep 0.1 & fg"

	# ============================================================================
	hr "Edge cases"

	test_cmd "empty input" ""
	test_cmd "spaces only" "    "
	test_cmd "tabs only" $'\t\t'
	test_cmd "many pipes" "echo a$(printf ' | cat%.0s' {1..20})"
	test_cmd "many redirs" "echo hi > /tmp/a > /tmp/b > /tmp/c && cat /tmp/c"
	test_cmd "large command" "echo \$(printf 'x%.0s' {1..10000})"
	test_cmd "lots of env vars" "$(for i in {1..50}; do printf 'export V$i=$i; '; done) echo \$V50"
	test_cmd "eval expansion" "eval echo hi"
	test_cmd "set/unset positional" "set -- a b c; echo \$2; unset 2"
	test_cmd "IFS test" "IFS=,:; set -- a,b,c; echo \$*"

	# ============================================================================
	hr "Traps and signals"

	test_cmd "trap execute" "trap 'echo caught' INT; kill -INT \$\$"
	test_cmd "trap remove" "trap - INT; echo test"
	test_cmd "trap exit" "trap 'echo bye' EXIT; true"

	# ============================================================================
	hr "POSIX compliance checks"

	test_cmd "builtin true" "type true; true"
	test_cmd "builtin false" "type false; false"
	test_cmd "command builtin" "command echo ok"
	test_cmd "command -v" "command -v echo"
	test_cmd "readonly" "readonly X=1; X=2"
	test_cmd "readonly var persists" "readonly X=5; echo \$X"
	test_cmd "readonly unset fail" "readonly X=1; unset X"
	test_cmd "test string compare" "[ a = a ] && echo eq"
	test_cmd "test int compare" "[ 3 -gt 2 ] && echo gt"
	test_cmd "case pattern" "case foo in f*) echo match;; esac"
	test_cmd "case default" "case bar in x) echo no;; *) echo yes;; esac"

	# ============================================================================
	hr "Cleanup / Misc"

	test_cmd "rm leftovers" "rm -rf /tmp/a /tmp/b /tmp/group.txt /tmp/redir*.txt /tmp/piperes.txt"
	test_cmd "end" "echo Done!"
}

# ===============================
# Main
# ===============================
trap 'rm -f /tmp/msh_* /tmp/bash_*' EXIT

print_header
setup_test_files
run_tests
summary
