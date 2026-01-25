/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:25:13 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 13:54:12 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <signal.h>

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

#include "allocator/allocator.h"
#include "env/env.h"
#include "util/prompt.h"
#include "util/help.h"
#include "parser/parser.h"
#include "cli/cli.h"
#include "vm/vm.h"
#include "core/stdio.h"
#include "core/string.h"
#include "core/stdlib.h"

#include "shell.h"

/**
 * @brief Gets or sets the global shell instance.
 *
 * @param sh Pointer to the shell structure to set, or NULL to get the current
 * instance
 * @return Pointer to the current shell instance.
 */
t_shell	*get_shell(t_shell *sh)
{
	static t_shell	*save = NULL;

	if (sh)
		save = sh;
	return (save);
}

/**
 * @brief Signal handler for SIGINT.
 *
 * @param sig Signal number
 */
static void	sig_handler(int sig)
{
	t_shell	*sh;

	sh = get_shell(0);
	if (!sh->vm.active)
	{
		if (sig == SIGINT)
			rl_replace_line("", 0);
		rl_clear_visible_line();
		rl_redraw_prompt_last_line();
		rl_redisplay();
	}
}

/**
 * @brief Destroys the shell structure and frees allocated resources.
 *
 * @param sh Pointer to the shell structure
 */
void	sh_destroy(t_shell *sh)
{
	vec_free(sh->vm.exit_codes);
	vec_free(sh->vm.pids);
	env_destroy(&sh->env);
	allocator_destroy(&sh->allocator);
	close(0);
	close(1);
	close(2);
}

/**
 * @brief Initializes signal handlers for SIGINT and SIGQUIT.
 */
static void	sh_init(t_shell *sh, int argc, char **argv, char **envp)
{
	ft_memset(sh, 0, sizeof(t_shell));
	get_shell(sh);
	allocator_init(&sh->allocator);
	expander_init(&sh->expander, sh);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	if (cli_init(&sh->cli, argc, argv) != RESULT_OK
		|| env_init(&sh->env, &sh->allocator, envp) != RESULT_OK
		|| parser_init(&sh->parser, &sh->lexer) != RESULT_OK
		|| vm_init(&sh->vm) != RESULT_OK)
	{
		ft_dprintf(2, "Error: failed to initialize minishell\n");
		sh_destroy(sh);
		_exit(2);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;
	int		exit_code;

	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		ft_dprintf(2, "Error: cannot run minishell in a pipeline\n");
		return (1);
	}
	sh_init(&sh, argc, argv, envp);
	rl_catch_signals = 0;
	rl_outstream = stderr;
	rl_instream = stdin;
	sh.vm.shell = &sh;
	sh.vm.allocator = &sh.allocator;
	exit_code = 0;
	if (cli_is_set(&sh.cli, "version"))
		help_version();
	else
		exit_code = repl(&sh);
	sh_destroy(&sh);
	return (exit_code);
}
