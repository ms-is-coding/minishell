TraSH - The Trash Shell, 0.0.0-beta
Copyright (C) 2025 ms-is-coding and SkarEye
License GPLv3: GNU GPL v.3 https://gnu.org/licenses/gpl-3.0.html

This program comes with ABSOLUTELY NO WARRANTY.
This is free software, and you are welcome to redistribute it.

TraSH (TraSH Recycles Again SHell) is a CLI program that attempts to reproduce
as best as it can the infamous Bash shell, following POSIX standard.
TraSH started out as a 'MiniShell' project, required by the 42 Common Core.

To install TraSH for yourself :

1 - Clone the Git Repository into a local working directory.

2 - Making use of the Makefile, when in the TraSH directory input the command :

	make <build_type>

With each build type being as specified :
	- default	:	explicitely runs the default Make rules.
	- debug		:	adds more compilation flags & debug symbols.
	- release	:	uses the flag '-O2' & for optimized program execution & adds
					forbidden features. Disables the debug asserts.
	- sanitize	:	attaches the ASAN, UBSAN & LSAN libraries, for address
					errors, undefined behavior & leaks respectively.
By default, the 'default' flag is used.

Other more traditional Make rules exist :
	- bonus		:
	- norm		:	executes the 42 'norminette', which checks if the code is
					written following strict 42 syntax.
	- postbuild	:
	- libft		:	recompiles the 'libft' library.
	- clean		:	removes object files & directory.
	- fclean	:	removes object files & directory, & executable.
	- re		:	recompiles all object files & executable.
	- tidy		:	executes 'clang-tidy', which checks for errors in the code.
	- test(WiP)	:	runs tests suites to check program robustness.

3 - Execute the newly created executable. Depending on the environment you are
working from, it can be named 'minishell' or 'TraSH'.
When executing, you can define certain flags :
	- --dissassemble (-d)	:
	Dissassembles and prints the bytecode of each executed command line.
	This does not work when working on the 'realease' version.

	- --verbose	(-v)		:	(NOT YET IMPLEMENTED)
	prints everything TraSH will do.

	- --version				:
	runs TraSH, prints the current version, exits.

	- --posix (-p)			:	(NOT YET IMPLEMENTED)
	removes some of the non-posix features.

And you're in ! TraSH uses AOT (Ahead Of Time) compilation to bytecode for
faster and more efficient command execution, such as more commonly used
binary tree execution.

TraSH also has some built-in functions ready to use :
	- cd
	- echo
	- env
	- exec
	- exit
	- export
	- false
	- logout
	- pwd
	- readonly
	- return
	- set
	- true
	- type
	- unset

For more information on these built-ins, use when in TraSH :

	help <builtin_name>

TraSH functions as close as it can to Bash, but isn't perfect and is prone to
bugs. If you find any, please feel free to reach out to ms-is-coding or SkarEye
so we can better the code and ourselves.

