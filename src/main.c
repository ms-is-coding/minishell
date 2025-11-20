/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:25:13 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/01 19:22:08 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <signal.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
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
#include "util/time.h"
#include "util/git.h"
#include "util/help.h"
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

static bool	had_newline(void)
{
	struct termios	oldt;
	struct termios	newt;
	int				row;
	int				col;
	char			buf[32];

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(unsigned)(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ft_printf("\033[6n");
	if (read(STDIN_FILENO, buf, sizeof(buf) - 1) > 0)
	{
		buf[sizeof(buf) - 1] = 0;
		if (sscanf(buf, "\033[%d;%dR", &row, &col) == 2
			&& col != 1)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
			ft_printf("\n");
			return (false);
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return (true);
}

static void	reset_prompt(void)
{
	struct termios	def;

	tcgetattr(STDIN_FILENO, &def);
	def.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &def);
}

static void	prompt_exit_codes(t_shell *sh, char *prompt)
{
	const char	*color;
	int			code;
	int			i;

	if (!had_newline())
		ft_snprintf(prompt, PROMPT_SIZE, ANSI_MAGENTA "⤶ " ANSI_RESET);
	color = ANSI_RED;
	if (ft_vector_at(&sh->vm.exit_codes, -1).value.i32 == 0)
		color = ANSI_GREEN;
	i = -1;
	while (++i < (int)sh->vm.exit_codes.length - 1)
	{
		code = ft_vector_at(&sh->vm.exit_codes, i).value.i32;
		if (code > 128 && code < 128 + 65 && kill_signals(code - 128))
			ft_snprintf(prompt, PROMPT_SIZE, "%s%s %s ",
				prompt, color, kill_signals(code - 128));
		else
			ft_snprintf(prompt, PROMPT_SIZE, "%s%s %i ",
				prompt, color, code);
	}
	code = ft_vector_at(&sh->vm.exit_codes, -1).value.i32;
	if (code > 128 && code < 128 + 65 && kill_signals(code - 128))
		ft_snprintf(prompt, PROMPT_SIZE, "%s%s %s " ANSI_RESET,
			prompt, color, kill_signals(code - 128));
	else
		ft_snprintf(prompt, PROMPT_SIZE, "%s%s %i " ANSI_RESET,
			prompt, color, code);
}

static void	prompt_git_status(
	__attribute__((unused)) t_shell *sh,
	char *prompt)
{
	char			git_prompt[64];
	t_git_status	git;

	git = git_status_read();
	if (git.branch[0] == '\0')
		return ;
	git_prompt[0] = '\0';
	ft_strlcat(git_prompt, ANSI_MAGENTA " ", 64);
	ft_strlcat(git_prompt, git.branch, 64);
	ft_strlcat(git_prompt, " ", 64);
	if (git.behind)
		ft_snprintf(git_prompt, 64, "%s%i", git_prompt, git.behind);
	if (git.ahead)
		ft_snprintf(git_prompt, 64, "%s%i", git_prompt, git.ahead);
	if (git.behind || git.ahead)
		ft_strlcat(git_prompt, " ", 64);
	if (git.staged)
		ft_snprintf(git_prompt, 64, "%s+%i", git_prompt, git.staged);
	if (git.dirty)
		ft_snprintf(git_prompt, 64, "%s%i", git_prompt, git.dirty);
	if (git.untracked)
		ft_snprintf(git_prompt, 64, "%s%i", git_prompt, git.untracked);
	if (git.staged || git.dirty || git.untracked)
		ft_strlcat(git_prompt, " ", 64);
	ft_strlcat(git_prompt, "", 64);
	ft_snprintf(prompt, PROMPT_SIZE, "%s" ANSI_MAGENTA "%s" ANSI_RESET,
		prompt, git_prompt);
}

static void	prompt_pwd(t_shell *sh, char *prompt)
{
	const char	*home;
	char		pwd[PATH_MAX];
	const char	*tmp;

	tmp = env_get(&sh->env, "PWD");
	if (tmp)
		ft_strlcpy(pwd, tmp, PATH_MAX);
	else
		getcwd(pwd, PATH_MAX);
	home = env_get(&sh->env, "HOME");
	if (ft_strstr(pwd, home))
		ft_snprintf(pwd, PATH_MAX, "~%s", pwd + ft_strlen(home));
	ft_snprintf(prompt, PROMPT_SIZE, "%s" ANSI_BLUE " %s " ANSI_RESET,
		prompt, pwd);
}

static void	prompt_time(__attribute__((unused)) t_shell *sh, char *prompt,
	int64_t delta)
{

	if (delta <= 0)
		return ;
	ft_snprintf(prompt, PROMPT_SIZE, "%s" ANSI_YELLOW " %lims " ANSI_RESET,
		prompt, delta);
}

static int	repl(t_shell *sh)
{
	int64_t		begin;
	int64_t		end;
	char		*line;
	t_result	result;
	char		prompt[PROMPT_SIZE];

	begin = 0;
	end = 0;
	while (1)
	{
		if (sh->vm.active)
			continue ;
		prompt[0] = '\0';
		prompt_exit_codes(sh, prompt);
		prompt_pwd(sh, prompt);
		prompt_git_status(sh, prompt);
		prompt_time(sh, prompt, end - begin - 1);
		ft_strlcat(prompt, " ", PROMPT_SIZE);
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
			begin = time_get();
			vm_run(&sh->vm, &sh->parser.program);
			end = time_get();
		}
		else
		{
			sh->vm.exit_codes.length = 0;
			ignore((void *)ft_vector_push(&sh->vm.exit_codes,
					ft_gen_val(TYPE_OTHER, (t_any){.i32 = 2})));
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
		return (2);
	if (cli_is_set(&sh->cli, "disassemble"))
		disasm(&sh->parser.program);
	vm_run(&sh->vm, &sh->parser.program);
	return (ft_vector_at(&sh->vm.exit_codes, -1).value.i32);
}

static void	sh_destroy(t_shell *sh)
{
	cli_destroy(&sh->cli);
	env_destroy(&sh->env);
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
	if (!sh->vm.active)
	{
		// if (sig == SIGINT)
		// 	rl_replace_line("", 0);
		//rl_clear_visible_line();
		//rl_redraw_prompt_last_line();
		rl_redisplay();
	}
}

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
		|| ft_vector_init(&sh.vm.exit_codes, 16) != RESULT_OK)
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
