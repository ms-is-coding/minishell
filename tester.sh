#!/bin/bash

RED=$'\033[0;31m'
GREEN=$'\033[0;32m'
YELLOW=$'\033[1;33m'
BLUE=$'\033[0;34m'
CYAN=$'\033[0;36m'
BOLD=$'\033[1m'
RESET=$'\033[0m'

TOTAL=0
PASSED=0
FAILED=0

print_header() {
    echo $CYAN"╭──────────────────╮"$RESET
    echo $CYAN"│ MINISHELL TESTER │"$RESET
    echo $CYAN"╰──────────────────╯"$RESET
    echo ""
}

print_section() {
    echo $'\n'$BLUE$BOLD"╶╶╶╶╶ $1 ╴╴╴╴╴"$RESET$'\n'
}

test_cmd() {
    local test_name="$1"
    local cmd="$2"

    TOTAL=$((TOTAL + 1))

    echo "exit" >> /tmp/minishell_test_cmd.txt
    timeout 2s ./minishell -c "$cmd" > /tmp/minishell_output.txt 2>&1
    local trash_exit=$?
    local trash_output=$(cat /tmp/minishell_output.txt)

    bash -c "$cmd" > /tmp/bash_output.txt 2>&1
    local bash_exit=$?
    local bash_output=$(cat /tmp/bash_output.txt)

    rm -f /tmp/minishell_test_cmd.txt /tmp/minishell_output.txt /tmp/bash_output.txt

    if [ "$trash_exit" -eq "$bash_exit" ]; then
        echo -e "${GREEN}✓${RESET} ${test_name}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗${RESET} ${test_name}: Exit codes differ (trash: $trash_exit, bash: $bash_exit)"
        FAILED=$((FAILED + 1))
    fi
}

check_minishell() {
    if [ ! -f "./minishell" ]; then
        echo -e $RED"Error: ./minishell does not exist"$RESET
        make -C .
    fi
}

setup_test_files() {
    echo "test content" > /tmp/test_file.txt
    echo "line1" > /tmp/test_input.txt
    echo "line2" >> /tmp/test_input.txt
    mkdir -p /tmp/test_dir
    touch /tmp/test_dir/file1.txt /tmp/test_dir/file2.c /tmp/test_dir/file3.txt
}

cleanup_test_files() {
    rm -f /tmp/test_file.txt /tmp/test_input.txt
    rm -rf /tmp/test_dir
    rm -f /tmp/minishell_*.txt /tmp/bash_output.txt
}

run_all_tests() {

    print_section "Builtins"

    test_cmd "echo" "echo Hello World"
    test_cmd "echo -n" "echo -n test"
    test_cmd "echo multiple args" "echo one two three"
    test_cmd "echo with spaces" "echo    multiple    spaces"
    test_cmd "empty echo" "echo"

    test_cmd "pwd" "pwd"
    test_cmd "pwd with args" "pwd extra"

    test_cmd "cd" "cd"
    test_cmd "cd /tmp" "cd /tmp"
    test_cmd "Invalid cd" "cd /nonexistent"
    test_cmd "cd -" "cd /tmp && cd - && pwd"
	test_cmd "Magic cd" "mkdir -p a/b && cd a/b && rm ../../a && cd .. && cd .. && pwd"

    test_cmd "env" "env"
    test_cmd "env with args" "env test"

    test_cmd "export NEW_VAR=test" "export NEW_VAR=test"
    test_cmd "Invalid export" "export 123=test"
    test_cmd "Export without value" "export TEST"

    test_cmd "unset" "export TEST=1 && unset TEST"
    test_cmd "Nonexistent unset" "unset NONEXISTENT"

    test_cmd "exit 0" "exit 0"
    test_cmd "exit 42" "exit 42"
    test_cmd "Invalid exit" "exit abc"
    test_cmd "Too many arguments exit" "exit a b"

    print_section "Environment"

    test_cmd "\$PATH exists" "echo \$PATH"
    test_cmd "\$HOME exists" "echo \$HOME"
    test_cmd "\$USER exists" "echo \$USER"
    test_cmd "success \$?" "true && echo \$?"
    test_cmd "error \$?" "false && echo \$?"
    test_cmd "no var" "echo \$NONEXISTENT"
    test_cmd "Export and use" "export TEST=hello && echo \$TEST"

    print_section "Quotes"

    test_cmd "Simple quotes" "echo 'hello world'"
    test_cmd "Double quotes" "echo \"hello world\""
    test_cmd "Single with \$" "echo '\$PATH'"
    test_cmd "Double with \$" "echo \"\$PATH\""
    test_cmd "Empty quotes" "echo ''"
    test_cmd "Mixed quotes" "echo 'single'\"double\""
    test_cmd "Nested quotes" "echo \"test 'nested' quote\""

    print_section "Redirs"

    test_cmd "Redir output >" "echo test > /tmp/test_out.txt"
    test_cmd "Redir input <" "cat < /tmp/test_file.txt"
    test_cmd "Redir append >>" "echo line1 > /tmp/test_append.txt && echo line2 >> /tmp/test_append.txt"
    test_cmd "Several redirs" "echo test > /tmp/out1.txt > /tmp/out2.txt"
    test_cmd "Nonexistent redir" "cat < /tmp/nonexistent.txt"
    test_cmd "Simple heredoc" "cat << EOF\ntest\nEOF"

    print_section "Pipes"

    test_cmd "Signle pipe" "echo hello | cat"
    test_cmd "Double pipe" "echo test | cat | cat"
	test_cmd "Triple pipe" "echo test | cat | cat | cat"
	test_cmd "Pipeline grep" "echo hello world | grep hello"
	test_cmd "Pipeline wc" "echo -e 'line1\nline2\nline3' | wc -l"

	print_section "Commands"

	test_cmd "ls" "ls"
	test_cmd "ls -l" "ls -l"
	test_cmd "cat" "cat /tmp/test_file.txt"
	test_cmd "grep" "grep test /tmp/test_file.txt"
	test_cmd "wc" "wc /tmp/test_file.txt"
	test_cmd "nonexistent" "nonexistentcommand"

	print_section "Paths"

	test_cmd "Absolute" "/bin/echo test"
	test_cmd "Relative" "./minishell --version"
	test_cmd "empty PATH" "export PATH='' && ls"

	print_section "Syntax"

	test_cmd "Beginning pipe" "| echo test"
	test_cmd "Ending pipe" "echo test |"
	test_cmd "Logical OR" "echo test || echo test"
	test_cmd "Unterminated string" "echo 'test"
    test_cmd "Redir no file" "echo test >"

    print_section "Special cases"

    test_cmd "Empty line" ""
    test_cmd "Spaces" "   "
    test_cmd "Tabs" "\t\t"
    test_cmd "Long command" "echo $(printf 'a%.0s' {1..1000})"
    test_cmd "Many spaces" "echo     test     with     spaces"
    test_cmd "Many pipes" "echo test$(printf ' | cat%.0s' {1..127})"

    print_section "Signals"

    echo $YELLOW"⚠"$RESET"  Ctrl+C: Clear prompt  │  Interrupt program"
    echo $YELLOW"⚠"$RESET"  Ctrl+D: Exit shell    │"
    echo $YELLOW"⚠"$RESET"  Ctrl+\: Nothing       │  Send SIGQUIT"

    print_section "Bonuses"

    test_cmd "AND success" "true && echo success"
    test_cmd "AND failure" "false && echo not_printed"
    test_cmd "OR success" "false || echo success"
    test_cmd "OR failure" "true || echo not_printed"
    test_cmd "Parenthesis" "(echo test)"
    test_cmd "Wildcards *" "echo /tmp/test_dir/*.txt"

    # ===== MEMORY LEAKS =====
    # print_section "12. MEMORY LEAKS (Valgrind)"

    if command -v valgrind &> /dev/null; then
        echo "Initiating leak check..."
        echo "echo test" | valgrind \
			--leak-check=full \
			--error-exitcode=1 \
			--show-leak-kinds=all \
			--suppressions=readline.supp \
			./minishell > /dev/null 2>&1
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}✓${RESET} No leaks detected"
        else
            echo -e "${RED}✗${RESET} Leaks detected"
        fi
    else
        echo -e "${YELLOW}⚠${RESET}  Valgrind not installed"
    fi
}

# ============================================================================
# MAIN
# ============================================================================

main() {
    print_header
    check_minishell
    setup_test_files

    echo -e "${CYAN}Starting tests...${RESET}\n"

    run_all_tests

    cleanup_test_files

    echo ""
    echo $CYAN"╭───────────────╮"$RESET
    echo $CYAN"│    RESULTS    │"$RESET
    echo $CYAN"├───────────────┤"$RESET
    printf $CYAN"│ "$RESET$BLUE"Total:%7d "$RESET$CYAN"│\n"$RESET $TOTAL
    printf $CYAN"│ "$RESET$GREEN"Success:%5d "$RESET$CYAN"│\n"$RESET $PASSED
    printf $CYAN"│ "$RESET$RED"Failure:%5d "$RESET$CYAN"│\n"$RESET $FAILED

    # Calculer le pourcentage
	if [ $TOTAL -gt 0 ]; then
		PERCENT=$((PASSED * 100 / TOTAL))
		if [ "$PERCENT" -gt 80 ]; then
			printf $CYAN"│ "$RESET"Score:"$GREEN$BOLD"%6d%% "$RESET$CYAN"│\n"$RESET $PERCENT
		elif [ "$PERCENT" -ge 40 ]; then
			printf $CYAN"│ "$RESET"Score:"$YELLOW$BOLD"%6d%% "$RESET$CYAN"│\n"$RESET $PERCENT
		else
			printf $CYAN"│ "$RESET"Score:"$RED$BOLD"%6d%% "$RESET$CYAN"│\n"$RESET $PERCENT
		fi
	fi

    echo $CYAN"╰───────────────╯"$RESET

    if [ $FAILED -eq 0 ]; then
        echo $'\n'$GREEN$BOLD"✓ All tests successful!"$RESET
        exit 0
    else
        echo $'\n'$RED$BOLD"✗ Test suite failed"$RESET
        exit 1
    fi
}

trap cleanup_test_files EXIT

main "$@"
