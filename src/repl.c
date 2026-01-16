/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:59:31 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/16 18:30:56 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <assert.h>
#include <sys/wait.h>

#include "util/prompt.h"
#include "parser/parser.h"
#include "disasm/disasm.h"
#include "cli/cli.h"
#include "vm/vm.h"
#include "core/stdio.h"
#include "core/stdlib.h"

#include "ansi.h"
#include "shell.h"
#include "repl.h"

/**
 * @brief Resets the terminal prompt settings.
 */
static void	reset_prompt(void)
{
	struct termios	def;

	tcgetattr(STDIN_FILENO, &def);
	def.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &def);
}

/**
 * @brief Checks the result of the parsing and executes the program if
 * successful.
 *
 * @param sh Pointer to the shell structure
 * @param result Result of the parsing operation
 */
static void	check_result(t_shell *sh, t_result result)
{
	if (result == RESULT_OK)
	{
		if (cli_is_set(&sh->cli, "disassemble"))
			disasm(&sh->parser.program);
		vm_run(&sh->vm, &sh->parser.program);
	}
	else
	{
		vec_clear(sh->vm.exit_codes);
		vec_push(sh->vm.exit_codes, (void *)2);
	}
}

int	repl(t_shell *sh)
{
	char		*line;
	t_result	result;
	const char	*prompt;

	sh->should_exit = false;
	while (!sh->should_exit)
	{
		if (sh->vm.active)
			continue ;
		prompt = generate_prompt(sh);
		reset_prompt();
		line = readline(prompt);
		if (!line)
			break ;
		add_history(line);
		ft_printf(ANSI_RESET);
		result = parser_parse(&sh->parser, line);
		check_result(sh, result);
		free(line);
	}
	return ((int32_t)(int64_t)vec_get(sh->vm.exit_codes, -1));
}
