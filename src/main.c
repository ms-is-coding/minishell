/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:25:13 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 23:37:27 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include "environ/environ.h"
#include "parser/parser.h"
#include "cli/cli.h"
#include "vm/vm.h"

#include "builtins.h"
#include "libft.h"
#include "ansi.h"
#include "shell.h"

#define MAX_OFFSET 16

__attribute__((__unused__))
static char	*find_exec(char *arg)
{
	const char	*paths[] = {
		"./", "/bin", "/usr/bin", "/usr/local/bin",
		"/sbin", "/usr/sbin", "/usr/local/sbin", NULL};
	char		*path;
	int			i;
	size_t		len;

	i = -1;
	if (!arg)
		return (NULL);
	while (paths[++i])
	{
		len = ft_strlen(paths[i]) + ft_strlen(arg) + 2;
		path = ft_malloc(len);
		if (!path)
			return (NULL);
		ft_snprintf(path, len, "%s/%s", paths[i], arg);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

struct s_builtin {
	const char		*cmd;
	t_builtin_fn	fn;
};

__attribute__((__unused__))
static t_builtin_fn	find_builtin(char *arg)
{
	static struct s_builtin	builtins[] = {
	{"cd", builtin_cd}, {"echo", builtin_echo}, {"exec", builtin_exec},
	{"exit", builtin_exit}, {"false", builtin_false}, {"true", builtin_true},
	{":", builtin_true}, {"pwd", builtin_pwd},
	{NULL, NULL}};
	int						i;

	i = -1;
	while (builtins[++i].fn)
	{
		if (ft_strcmp(builtins[i].cmd, arg) == 0)
			return (builtins[i].fn);
	}
	return (NULL);
}

static void print_bytes(int bytes, t_program *program, size_t *offset, const char *desc)
{
	int	i;

	assert(bytes <= MAX_OFFSET);
	i = -1;
	while (++i < bytes)
		ft_printf("%02x ", program->data[(*offset)++]);
	i = bytes - 1;
	while (++i < MAX_OFFSET)
		ft_printf("   ");
	ft_printf("%s\n", desc);
}

__attribute__((__unused__))
static void	disassemble(t_program *program)
{
	size_t len;
	for (size_t offset = 0; offset < program->len;) {
		ft_printf(" %04lx: ", offset);

		switch (program->data[offset]) {
			case OP_NULL:     print_bytes(1, program, &offset, "NULL"); break;
			case OP_EXE:      print_bytes(1, program, &offset, "EXEC"); break;
			case OP_CMD:      print_bytes(5, program, &offset, "COMMAND"); break;
			case OP_ARG:
				len = program->data[offset + 1];
				print_bytes((int)len + 2, program, &offset, "ARG");
				break;
			case OP_FNAME:
				len = program->data[offset + 1];
				print_bytes((int)len + 2, program, &offset, "FILENAME");
				break;
			case OP_PIPE:     print_bytes(1, program, &offset, "PIPE"); break;
			case OP_OUT:      print_bytes(5, program, &offset, "REDIR_OUT"); break;
			case OP_JZ:       print_bytes(5, program, &offset, "JZ"); break;
			case OP_JNZ:      print_bytes(5, program, &offset, "JNZ"); break;
			case OP_IN:       print_bytes(1, program, &offset, "REDIR_IN"); break;
			case OP_WAIT:     print_bytes(1, program, &offset, "WAIT"); break;
			default:          print_bytes(1, program, &offset, "UNKNOWN");
		}
	}
}

static int	repl(t_shell *sh)
{
	char		*line;
	t_result	result;

	while (1)
	{
		line = readline(ANSI_BOLD ANSI_GREEN "$" ANSI_RESET " ");
		if (!line)
			break ;
		add_history(line);
		ft_printf(ANSI_RESET); // what the fuck
		result = parser_parse(&sh->parser, line);
		if (result == RESULT_OK)
		{
			if (cli_is_set(&sh->cli, "disassemble"))
				disassemble(&sh->parser.program);
			vm_run(&sh->vm, &sh->parser.program);
		}
		free(line);
	}
	ft_printf("exit\n");
	return (0);
}

static t_result command(t_shell *sh, char *command)
{
	t_result	result;

	result = parser_parse(&sh->parser, command);
	if (result != RESULT_OK)
		return (RESULT_ERROR);
	return (vm_run(&sh->vm, &sh->parser.program));
}

t_result	environ_init(t_environ	*env, char **envp)
{
	t_result	result;

	(void)env;
	ft_vector_init(&env->public, 64);
	ft_vector_init(&env->private, 8);
	while (*envp)
	{
		result = ft_vector_push(&env->public,
				ft_gen_val(TYPE_OTHER, (t_any){.str = *envp}));
		if (result != RESULT_OK)
			return (RESULT_ERROR);
		envp++;
	}
	return (RESULT_OK);
}

static void	sh_destroy(t_shell *sh)
{
	cli_destroy(&sh->cli);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		sh;
	int			exit_code;

	if (cli_init(&sh.cli, argc, argv) != RESULT_OK
		|| environ_init(&sh.env, envp) != RESULT_OK
		|| parser_init(&sh.parser, &sh.lexer) != RESULT_OK)
	{
		sh_destroy(&sh);
		return (2);
	}
	if (cli_is_set_short(&sh.cli, 'c'))
		exit_code = command(&sh, cli_get_short(&sh.cli, 'c'));
	else
		exit_code = repl(&sh);
	return (exit_code);
}
