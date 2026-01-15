/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:25:13 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/15 15:20:54 by smamalig         ###   ########.fr       */
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
#include "util/time.h"
#include "util/help.h"
#include "parser/parser.h"
#include "disasm/disasm.h"
#include "cli/cli.h"
#include "vm/vm.h"
#include "core/stdio.h"
#include "core/string.h"
#include "core/stdlib.h"

#include "ansi.h"
#include "shell.h"

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

static int	repl(t_shell *sh) // FIX not commented, needs to still be split
{
	char		*line;
	t_result	result;
	char		prompt[PROMPT_SIZE];
	ssize_t		len;

	while (1)
	{
		if (sh->vm.active)
			continue ;
		len = 0;
		prompt[0] = '\0';
		prompt_user(sh, prompt, &len);
		prompt_pwd(sh, prompt, &len);
		prompt_exit_codes(sh, prompt, &len);
		ft_strlcat(prompt, "> ", PROMPT_SIZE);
		reset_prompt();
		line = readline(prompt);
		if (!line)
			break ;
		add_history(line);
		ft_printf(ANSI_RESET);
		result = parser_parse(&sh->parser, line);
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
		free(line);
	}
	ft_printf("exit\n");
	return ((int32_t)(int64_t)vec_get(sh->vm.exit_codes, -1));
}

/**
 * @brief Executes a single command.
 *
 * @param sh Pointer to the shell structure
 * @param command Command string to execute
 * @return Exit code of the command execution.
 */
static int	command(t_shell *sh, char *command)
{
	t_result	result;

	result = parser_parse(&sh->parser, command);
	if (result != RESULT_OK)
		return (2);
	if (cli_is_set(&sh->cli, "disassemble"))
		disasm(&sh->parser.program);
	vm_run(&sh->vm, &sh->parser.program);
	return ((int32_t)(int64_t)vec_get(sh->vm.exit_codes, -1));
}

/**
 * @brief Destroys the shell structure and frees allocated resources.
 *
 * @param sh Pointer to the shell structure
 */
void	sh_destroy(t_shell *sh)
{
	cli_destroy(&sh->cli);
	vec_free(sh->vm.exit_codes);
	vec_free(sh->vm.pids);
	env_destroy(&sh->env);
	allocator_destroy(&sh->allocator);
}

/**
 * @brief Gets or sets the global shell instance.
 *
 * @param sh Pointer to the shell structure to set, or NULL to get the current
 * instance
 * @return Pointer to the current shell instance.
 */
static t_shell	*get_shell(t_shell *sh)
{
	static t_shell	*save = NULL;

	if (sh)
		save = sh;
	return (save);
}

/**
 * @brief Signal handler for SIGINT and SIGQUIT.
 *
 * @param sig Signal number
 */
static void	handler(int sig)
{
	t_shell	*sh;

	sh = get_shell(0);
	vm_dispatch(&sh->vm, sig);
	if (!sh->vm.active)
	{
		// if (sig == SIGINT)
		// 	rl_replace_line("", 0);
		//rl_clear_visible_line();
		//rl_redraw_prompt_last_line();
		rl_redisplay();
	}
}

/**
 * @brief Initializes signal handlers for SIGINT and SIGQUIT.
 */
static void	signal_init(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

static void	test(t_shell *sh)
{
	char		buffer[1024];
	const char	*filename;
	int			fd;
	ssize_t		read_size;
	int			i;

	i = -1;
	while (++i < sh->cli.pos_i)
	{
		filename = sh->cli.positional[i];
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			ft_printf("----- OPEN ERROR -----\n");
			continue ;
		}
		read_size = read(fd, buffer, 1024);
		if (read_size == -1)
		{
			ft_printf("----- READ ERROR -----\n");
			continue ;
		}
		if (read_size == 1024)
		{
			ft_printf("----- PARTIAL DATA -----\n");
			continue ;
		}
		buffer[read_size] = 0;
		parser_parse(&sh->parser, buffer);
		vm_run(&sh->vm, &sh->parser.program);
		close(fd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell				sh;
	int					exit_code;

	ft_memset(&sh, 0, sizeof(t_shell));
	get_shell(&sh);
	allocator_init(&sh.allocator);
	expander_init(&sh.expander, &sh);
	signal_init();
	if (cli_init(&sh.cli, argc, argv) != RESULT_OK
		|| env_init(&sh.env, &sh.allocator, envp) != RESULT_OK
		|| parser_init(&sh.parser, &sh.lexer) != RESULT_OK
		|| vm_init(&sh.vm) != RESULT_OK)
	{
		sh_destroy(&sh);
		return (2);
	}
	rl_outstream = stderr;
	rl_instream = stdin;
	sh.vm.shell = &sh;
	sh.vm.allocator = &sh.allocator;
	if (cli_is_set(&sh.cli, "login"))
		ft_printf("Running as login shell\n");
	if (cli_is_set_short(&sh.cli, 'c'))
		exit_code = command(&sh, cli_get_short(&sh.cli, 'c'));
	else if (cli_is_set(&sh.cli, "version"))
	{
		help_version();
		exit_code = 0;
	}
	else if (sh.cli.pos_i > 0)
	{
		test(&sh);
		sh_destroy(&sh);
		exit(0);
	}
	else
		exit_code = repl(&sh);
	sh_destroy(&sh);
	return (exit_code);
}
