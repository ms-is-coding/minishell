# TraSH - The Trash Shell

TraSH (TraSH Replaces Another SHell) is a custom shell inspired by
the infamous Bash shell, following the POSIX standard.
TraSH started out as a 'MiniShell' project, required by the 42 Common Core.
The commands are AoT-compiled to bytecode for faster and more efficient command
execution, instead of the more commonly used abstact syntax tree execution.

## Installation

1. Make sure you have the tools to compile this project installed. You can get
them by running:
```
sudo apt update && sudo apt install build-essentials
```
or your distribution's equivalent.

2. Clone this repository

```
# using HTTPS
git clone https://github.com/ms-is-coding/minishell.git
```
```
# or using SSH
git clone git@github.com:ms-is-coding/minishell.git
```

## Build Instructions

TraSH has several available build targets:
| Target   | Description                                      |
|----------|--------------------------------------------------|
| default  | explicitely runs the default Make rules.         |
| debug    | adds stricter compilation flags & debug symbols. |
| release  | enables compiler optimizations & adds extra features. Disables the debug asserts. |
| sanitize | attaches the ASAN, UBSAN & LSAN libraries, for address errors, undefined behavior & leaks respectively. |

By default, the 'default' flag is used.

Other more traditional Make rules exist:
| Rule      | Description                                     |
|-----------|-------------------------------------------------|
| bonus     | builds the project using 'release'.             |
| norm      | executes the 42 'norminette', which checks if the code is written following strict 42 syntax. |
| postbuild | if the executable exists and is up to date, copies it to the root directory |
| libft     | recompiles the 'libft' library.                 |
| clean     | removes object files & directory.               |
| fclean    | removes object files & directory, & executable. |
| re        | recompiles all object files & executable.       |
| tidy      | executes 'clang-tidy', which checks for errors in the code. |
| test(WiP) | runs tests suites to check program robustness.  |

## Running

3 - Execute the newly created executable. Depending on the environment you are
working from, it can be named 'minishell' or 'trash'.

When executing, you can define certain flags:
| Flag                | Description                           |
|---------------------|---------------------------------------|
| --dissassemble (-d) | Dissassembles and prints the bytecode of each executed command line. This does not work when working on the 'realease' version. |
| --verbose (-v)      | (NOT YET IMPLEMENTED) prints everything TraSH will do.|
| --version           | runs TraSH, prints the current version, exits. |
| --posix (-p)        | (NOT YET IMPLEMENTED) removes some of the non-posix features. |

## Usage

TraSH can be used like any other shell, and exposes the following built-ins for
quality-of-life:
`cd`, `echo`, `env`, `exec`, `exit`, `export`, `false`, `logout`, `pwd`,
`readonly`, `return`, `set`, `true`, `type`, `unset`, `help`

For more information on these built-ins, run `help <builtin_name>` in TraSH

## Contributing

TraSH functions as close as it can to Bash, but isn't perfect and is prone to
bugs. If you find any, please feel free to open an issue.

## License

Copyright (C) 2025 ms-is-coding and SkarEye
License GPLv3: GNU GPL v.3 https://gnu.org/licenses/gpl-3.0.html

This program comes with ABSOLUTELY NO WARRANTY.
This is free software, and you are welcome to redistribute it.

See [LICENSE](LICENSE) for more details.
