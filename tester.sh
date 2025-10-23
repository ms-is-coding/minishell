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
	hr "MANDATORY PART – Builtins & Shell Basics"

	test_cmd "prompt & simple command" "echo Hello"
	test_cmd "search PATH executable" "ls"
	test_cmd "absolute path exec" "/bin/echo hi"
	test_cmd "builtin echo -n" "echo -n test"
	test_cmd "builtin cd relative" "mkdir -p /tmp/mshell_cd && cd /tmp/mshell_cd && pwd"
	test_cmd "builtin cd absolute" "cd / && pwd"
	test_cmd "builtin cd invalid" "cd /no/such && echo should_not"
	test_cmd "builtin pwd no args" "cd /tmp && pwd"
	test_cmd "builtin export simple" "export FOO=bar && echo \$FOO"
	test_cmd "builtin export list" "export | grep FOO"
	test_cmd "builtin unset simple" "export TMP=1 && unset TMP && echo \$TMP"
	test_cmd "builtin env no args" "env | sort | grep TERM"
	test_cmd "builtin exit no args" "exit"
	test_cmd "builtin exit with code" "exit 42"
	test_cmd "single redirection input" "echo foo > /tmp/mshell_out && cat < /tmp/mshell_out"
	test_cmd "single redirection output append" "echo a > /tmp/mshell_app && echo b >> /tmp/mshell_app && cat /tmp/mshell_app"
	test_cmd "here-doc simple" "cat <<EOF\nline1\nline2\nEOF"
	test_cmd "pipe single" "echo hi | tr H h"
	test_cmd "pipe multiple" "echo a b c | wc -w"
	test_cmd "variable expansion simple" "export X=123 && echo \$X"
	test_cmd "exit status expansion" "false; echo \$?"
	test_cmd "signal Ctrl-C simulation" "kill -INT \$\$ && echo after_signal"

	hr "BONUS PART – &&, ||, wildcards"

	test_cmd "logical AND success" "true && echo yes"
	test_cmd "logical AND failure" "false && echo no"
	test_cmd "logical OR success" "false || echo fallback"
	test_cmd "logical OR failure" "true || echo no"
	test_cmd "mixed AND/OR chain" "false && echo no || echo yes"
	test_cmd "parentheses grouping" "( false && echo no ) || ( true && echo yes )"
	test_cmd "wildcard simple" "touch /tmp/mshell_wild1 /tmp/mshell_wild2 && echo /tmp/mshell_wild*"
	test_cmd "wildcard no match" "echo /tmp/doesnotmatch*"
	test_cmd "wildcard mixed pattern" "mkdir -p /tmp/mshell_dir && touch /tmp/mshell_dir/fileA /tmp/mshell_dir/fileB && echo /tmp/mshell_dir/file*"
}

# ===============================
# Main
# ===============================
trap 'rm -f /tmp/msh_* /tmp/bash_*' EXIT

print_header
setup_test_files
run_tests
summary
