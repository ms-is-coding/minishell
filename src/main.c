/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:25:13 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/05 00:58:51 by smamalig         ###   ########.fr       */
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
#include "environ/environ.h"
#include "parser/parser.h"
#include "cli/cli.h"
#include "vm/vm.h"

#include "libft.h"
#include "ansi.h"
#include "shell.h"

#define MAX_OFFSET 16

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
	size_t	len;

	for (size_t offset = 0; offset < program->len;)
	{
		ft_printf(" %04lx: ", offset);
		switch (program->data[offset])
		{
			case OP_NULL:
				print_bytes(1, program, &offset, "NULL");
			break ;
			case OP_EXE:
				print_bytes(1, program, &offset, "EXEC");
			break ;
			case OP_CMD:
				print_bytes(5, program, &offset, "COMMAND");
			break ;
			case OP_ARG:
				len = program->data[offset + 1];
			print_bytes((int)len + 2, program, &offset, "ARG");
			break ;
			case OP_FNAME:
				len = program->data[offset + 1];
			print_bytes((int)len + 2, program, &offset, "FILENAME");
			break ;
			case OP_PIPE:
				print_bytes(1, program, &offset, "PIPE");
			break ;
			case OP_OUT:
				print_bytes(5, program, &offset, "REDIR_OUT");
			break ;
			case OP_JZ:
				print_bytes(5, program, &offset, "JZ");
			break ;
			case OP_JNZ:
				print_bytes(5, program, &offset, "JNZ");
			break ;
			case OP_IN:
				print_bytes(1, program, &offset, "REDIR_IN");
			break ;
			case OP_WAIT:
				print_bytes(1, program, &offset, "WAIT");
			break ;
			default :
				print_bytes(1, program, &offset, "UNKNOWN");
		}
	}
}

#define PROMPT_SIZE 0x100

static int	repl(t_shell *sh)
{
	char		*line;
	t_result	result;
	int			i;
	char		prompt_buf[PROMPT_SIZE];

	ft_printf(ANSI_BOLD ANSI_CYAN
		"🗑️ Welcome to TRASH Replaces Another Shell\n" ANSI_RESET);
	while (1)
	{
		i = -1;
		prompt_buf[0] = '\0';
		while (++i < (int)sh->vm.exit_codes.length - 1)
		{
			ft_snprintf(prompt_buf, PROMPT_SIZE, "%s" ANSI_RED " %i |",
				prompt_buf, ft_vector_at(&sh->vm.exit_codes, i).value.i32);
		}
		ft_snprintf(prompt_buf, PROMPT_SIZE, "%s" ANSI_RED " %i " ANSI_RESET
			ANSI_BOLD ANSI_GREEN "$ " ANSI_RESET,
			prompt_buf, ft_vector_at(&sh->vm.exit_codes, -1).value.i32);
		line = readline(prompt_buf);
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

static int	command(t_shell *sh, char *command)
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
	ft_vector_free(&sh->environ.public);
	ft_vector_free(&sh->environ.private);
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
	ft_printf("\n");
}

static void	signal_init(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell				sh;
	int					exit_code;

	get_shell(&sh);
	allocator_init(&sh.allocator);
	signal_init();
	if (cli_init(&sh.cli, argc, argv) != RESULT_OK
		|| environ_init(&sh.environ, envp) != RESULT_OK
		|| parser_init(&sh.parser, &sh.lexer) != RESULT_OK
		|| ft_vector_init(&sh.vm.exit_codes, 16) != RESULT_OK)
	{
		sh_destroy(&sh);
		return (2);
	}
	sh.vm.shell = &sh;
	sh.vm.allocator = &sh.allocator;
	if (cli_is_set_short(&sh.cli, 'c'))
		exit_code = command(&sh, cli_get_short(&sh.cli, 'c'));
	else
		exit_code = repl(&sh);
	sh_destroy(&sh);
	return (exit_code);
}
