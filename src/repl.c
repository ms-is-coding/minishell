/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:59:31 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/25 11:10:19 by smamalig         ###   ########.fr       */
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

#include "core/string.h"
#include "util/prompt.h"
#include "parser/parser.h"
#include "disasm/disasm.h"
#include "cli/cli.h"
#include "vm/vm.h"
#include "core/stdio.h"
#include "core/stdlib.h"

#include "ansi.h"
#include "shell.h"

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

static int	is_empty_line(char *line)
{
	return (ft_strspn(line, " \t\n\v\r") == ft_strlen(line));
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
		line = readline(prompt);
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		if (is_empty_line(line))
			continue ;
		ft_printf(ANSI_RESET);
		result = parser_parse(&sh->parser, line);
		check_result(sh, result);
		free(line);
	}
	return ((int32_t)(int64_t)vec_get(sh->vm.exit_codes, -1));
}
