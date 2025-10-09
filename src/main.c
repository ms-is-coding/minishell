/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:25:13 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/09 15:20:10 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <assert.h>
#include <sys/wait.h>

#include "allocator/allocator.h"
#include "env/env.h"
#include "parser/parser.h"
#include "disasm/disasm.h"
#include "cli/cli.h"
#include "vm/vm.h"

#include "libft.h"
#include "ansi.h"
#include "shell.h"

#define PROMPT_SIZE 0x100

static const char	*kill_signals(int sig)
{
	return ((const char *[65]){[1] = "HUP", [2] = "INT", [3] = "QUIT",
		[4] = "ILL", [5] = "TRAP", [6] = "ABRT", [7] = "BUS",
		[8] = "FPE", [9] = "KILL", [10] = "USR1", [11] = "SEGV", [12] = "USR2",
		[13] = "PIPE", [14] = "ALRM", [15] = "TERM", [16] = "STKFLT",
		[17] = "CHLD", [18] = "CONT", [19] = "STOP", [20] = "TSTP",
		[21] = "TTIN", [22] = "TTOU", [23] = "URG", [24] = "XCPU",
		[25] = "XFSZ", [26] = "VTALRM", [27] = "PROF", [28] = "WINCH",
		[29] = "POLL", [30] = "PWR", [31] = "SYS", [34] = "RTMIN",
		[64] = "RTMAX"}[sig]);
}

static int	repl(t_shell *sh)
{
	char		*line;
	t_result	result;
	int			i;
	char		prompt_buf[PROMPT_SIZE];
	const char	*color;
	int			code;

	while (1)
	{
		if (sh->vm.active)
			continue ;
		i = -1;
		prompt_buf[0] = '\0';
		color = ANSI_RED;
		if (ft_vector_at(&sh->vm.exit_codes, -1).value.i32 == 0)
			color = ANSI_GREEN;
		while (++i < (int)sh->vm.exit_codes.length - 1)
		{
			code = ft_vector_at(&sh->vm.exit_codes, i).value.i32;
			if (code > 128 && code < 128 + 65 && kill_signals(code - 128))
				ft_snprintf(prompt_buf, PROMPT_SIZE, "%s%s %s ",
					prompt_buf, color, kill_signals(code - 128));
			else
				ft_snprintf(prompt_buf, PROMPT_SIZE, "%s%s %i ",
					prompt_buf, color, code);
		}
		code = ft_vector_at(&sh->vm.exit_codes, -1).value.i32;
		if (code > 128 && code < 128 + 65 && kill_signals(code - 128))
			ft_snprintf(prompt_buf, PROMPT_SIZE, "%s%s %s " ANSI_RESET
				ANSI_BOLD ANSI_CYAN " " ANSI_RESET,
				prompt_buf, color, kill_signals(code - 128));
		else
			ft_snprintf(prompt_buf, PROMPT_SIZE, "%s%s %i " ANSI_RESET
				ANSI_BOLD ANSI_CYAN " " ANSI_RESET,
				prompt_buf, color, code);
		line = readline(prompt_buf);
		if (!line)
			break ;
		add_history(line);
		ft_printf(ANSI_RESET); // what the fuck
		result = parser_parse(&sh->parser, line);
		if (result == RESULT_OK)
		{
			if (cli_is_set(&sh->cli, "disassemble"))
				disasm(&sh->parser.program);
			vm_run(&sh->vm, &sh->parser.program);
		}
		else
		{
			sh->vm.exit_codes.length = 0;
			ft_vector_push(&sh->vm.exit_codes,
				ft_gen_val(TYPE_OTHER, (t_any){.i32 = 2}));
		}
		free(line);
	}
	ft_printf("exit\n");
	return (ft_vector_at(&sh->vm.exit_codes, -1).value.i32);
}

static int	command(t_shell *sh, char *command)
{
	t_result	result;

	result = parser_parse(&sh->parser, command);
	if (result != RESULT_OK)
		return (RESULT_ERROR);
	vm_run(&sh->vm, &sh->parser.program);
	return (ft_vector_at(&sh->vm.exit_codes, -1).value.i32);
}

static void	sh_destroy(t_shell *sh)
{
	cli_destroy(&sh->cli);
	ft_vector_free(&sh->vm.exit_codes);
	allocator_destroy(&sh->allocator);
}

static t_shell	*get_shell(t_shell *sh)
{
	static t_shell	*save = NULL;

	if (sh)
		save = sh;
	return (save);
}

void	vm_dispatch(t_vm *vm, int sig);

static void	handler(int sig)
{
	t_shell	*sh;

	sh = get_shell(0);
	vm_dispatch(&sh->vm, sig);
	write(STDOUT_FILENO, "\n", 1);
	if (sig == SIGINT && !sh->vm.active)
	{
		rl_on_new_line();
//		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	signal_init(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

static void	print_version(void)
{
	ft_printf("trash, version " TRASH_VERSION "\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_shell				sh;
	int					exit_code;

	ft_memset(&sh, 0, sizeof(t_shell));
	get_shell(&sh);
	allocator_init(&sh.allocator);
	signal_init();
	if (cli_init(&sh.cli, argc, argv) != RESULT_OK
		|| env_init(&sh.env, &sh.allocator, envp) != RESULT_OK
		|| parser_init(&sh.parser, &sh.lexer) != RESULT_OK
		|| ft_vector_init(&sh.vm.exit_codes, 16) != RESULT_OK)
	{
		sh_destroy(&sh);
		return (2);
	}
	sh.vm.shell = &sh;
	sh.vm.allocator = &sh.allocator;
	if (cli_is_set(&sh.cli, "login"))
		ft_printf("Running as login shell\n");
	if (cli_is_set_short(&sh.cli, 'c'))
		exit_code = command(&sh, cli_get_short(&sh.cli, 'c'));
	else if (cli_is_set(&sh.cli, "version"))
	{
		print_version();
		exit_code = 0;
	}
	else
		exit_code = repl(&sh);
	sh_destroy(&sh);
	return (exit_code);
}
