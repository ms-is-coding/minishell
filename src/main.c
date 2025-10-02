/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:25:13 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 13:24:49 by smamalig         ###   ########.fr       */
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
#include <wait.h>

#include "ansi.h"
#include "arguments.h"
#include "builtins.h"
#include "environment.h"
#include "libft.h"
#include "parser.h"
#include "shell.h"

#define MAX_OFFSET 16

static t_shell			g_sh;

static void	ft_waitpid(size_t idx, t_value val);

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

static void print_bytes(int bytes, t_chunk *chunk, size_t *offset, const char *desc)
{
	int	i;

	assert(bytes <= MAX_OFFSET);
	i = -1;
	while (++i < bytes)
		ft_printf("%02x ", chunk->data[(*offset)++]);
	i = bytes - 1;
	while (++i < MAX_OFFSET)
		ft_printf("   ");
	ft_printf("%s\n", desc);
}

__attribute__((__unused__))
static void	disassemble(t_chunk *chunk)
{
	size_t len;
	for (size_t offset = 0; offset < chunk->len;) {
		ft_printf(" %04lx: ", offset);

		switch (chunk->data[offset]) {
			case OP_NULL:     print_bytes(1, chunk, &offset, "NULL"); break;
			case OP_EXEC:     print_bytes(1, chunk, &offset, "EXEC"); break;
			case OP_COMMAND:
				len = chunk->data[offset + 1];
				print_bytes((int)len + 2, chunk, &offset, "COMMAND");
				break;
			case OP_ARG:
				len = chunk->data[offset + 1];
				print_bytes((int)len + 2, chunk, &offset, "ARG");
				break;
			case OP_FILENAME:
				len = chunk->data[offset + 1];
				print_bytes((int)len + 2, chunk, &offset, "FILENAME");
				break;
			case OP_PIPE:     print_bytes(1, chunk, &offset, "PIPE"); break;
			case OP_REDIR_OUT:print_bytes(5, chunk, &offset, "REDIR_OUT"); break;
			case OP_JZ:       print_bytes(5, chunk, &offset, "JZ"); break;
			case OP_JNZ:      print_bytes(5, chunk, &offset, "JNZ"); break;
			case OP_REDIR_IN: print_bytes(1, chunk, &offset, "REDIR_IN"); break;
			case OP_WAIT:     print_bytes(1, chunk, &offset, "WAIT"); break;
			default:
				print_bytes(1, chunk, &offset, "UNKNOWN");
		}
	}
}

typedef void (*t_exec_fn)(t_chunk *chunk, size_t *ip);

typedef struct s_stack_frame
{
	char					*stack[128];
	size_t					sp;
	struct s_stack_frame	*next;
}	t_stack_frame;

static t_stack_frame *frames = NULL;

static t_stack_frame	*push_stack_frame(void)
{
	t_stack_frame	*temp;
	t_stack_frame	*frame;

	temp = frames;
	frame = malloc(sizeof(t_stack_frame));
	if (!frame)
		return (NULL);
	frame->next = temp;
	frame->sp = 0;
	frames = frame;
	return (frame);
}

static void	pop_stack_frame(void)
{
	t_stack_frame	*temp;

	if (!frames)
		return ;
	temp = frames->next;
	free(frames);
	frames = temp;
}

static void	exec_op_wait(t_chunk *chunk, size_t *ip)
{
	ft_vector_foreach(&g_sh.pids, ft_waitpid);
	g_sh.pids.length = 0;
	(void)chunk;
	(void)ip;
}

static void	exec_op_command(t_chunk *chunk, size_t *ip)
{
	t_stack_frame	*frame;
	size_t			len;

	frame = push_stack_frame();
	len = chunk->data[++(*ip)];
	frame->stack[frame->sp++] = ft_strndup((char *)chunk->data + *ip + 1, len);
	*ip += len;
}


static void	exec_op_arg(t_chunk *chunk, size_t *ip)
{
	t_stack_frame	*frame;
	size_t			len;

	frame = frames;
	len = chunk->data[++(*ip)];
	frame->stack[frame->sp++] = ft_strndup((char *)chunk->data + *ip + 1, len);
	*ip += len;
}

static char **env;

static void	push_env(size_t idx, t_value val)
{
	env[idx] = val.value.str;
}

static void exec_op_exec(t_chunk *chunk, size_t *ip)
{
	t_stack_frame *frame;
	char *exec;
	t_builtin_fn builtin;
	int pid;

	env = malloc(sizeof(char *) * (g_sh.env.public.length + 1));
	if (!env)
		return;
	ft_vector_foreach(&g_sh.env.public, push_env);
	env[g_sh.env.public.length] = NULL;

	frame = frames;
	frame->stack[frame->sp++] = NULL;

	builtin = find_builtin(frame->stack[0]);
	if (builtin == builtin_exec || builtin == builtin_exit) {
		builtin(&g_sh, (int)frame->sp - 1, frame->stack);
		exit(0);
	}
	pid = fork();
	if (pid == 0) {
		if (g_sh.prev_fd != 0)
			dup2(g_sh.prev_fd, STDIN_FILENO);
		if (g_sh.pipefd[1] != 1)
			dup2(g_sh.pipefd[1], STDOUT_FILENO);
		if (g_sh.prev_fd != 0)
			close(g_sh.prev_fd);
		if (g_sh.pipefd[0] != 0)
			close(g_sh.pipefd[0]);
		if (g_sh.pipefd[1] != 1)
			close(g_sh.pipefd[1]);
		builtin = find_builtin(frame->stack[0]);
		if (builtin) {
			builtin(&g_sh, (int)frame->sp - 1, frame->stack);
			exit(0);
		}
		exec = find_exec(frame->stack[0]);
		execve(exec, frame->stack, env);
		free(exec);
		ft_printf("execve failed: %m\n");
		exit(1);
	}
	else if (pid < 0)
		ft_printf("fork failed: %m\n");
	if (g_sh.prev_fd != 0)
		close(g_sh.prev_fd);
	if (g_sh.pipefd[1] != 1)
		close(g_sh.pipefd[1]);
	g_sh.prev_fd = g_sh.pipefd[0];
	g_sh.pipefd[0] = 0;
	g_sh.pipefd[1] = 1;
	ft_vector_push(&g_sh.pids, ft_gen_val(TYPE_OTHER, (t_any){.i32 = pid}));
	pop_stack_frame();
	free(env);
	(void)chunk;
	(void)ip;
}

static void exec_op_pipe(t_chunk *chunk, size_t *ip)
{
	if (pipe(g_sh.pipefd) < 0) {
		ft_printf("pipe failed: %m\n");
		return;
	}
	exec_op_exec(chunk, ip);
}


static void	exec_op_filename(t_chunk *chunk, size_t *ip)
{
	size_t	len;

	len = chunk->data[++(*ip)];
	*ip += len;
}

static void	exec_op_background(t_chunk *chunk, size_t *ip)
{
	(void)chunk;
	(void)ip;
}

static void	exec_op_redir_out(t_chunk *chunk, size_t *ip)
{
	*ip += 4;
	(void)chunk;
	(void)ip;
}

static void	exec_op_redir_in(t_chunk *chunk, size_t *ip)
{
	(void)chunk;
	(void)ip;
}

static void	exec_op_jump(t_chunk *chunk, size_t *ip)
{
	int32_t	jmp_pos;

	(*ip)++;
	memcpy(&jmp_pos, chunk->data + *ip, sizeof(int32_t));
	*ip = jmp_pos - 1;
}

static void	ft_waitpid(size_t idx, t_value val)
{
	int	stat;

	(void)idx;
	waitpid(val.value.i32, &stat, 0);
}

static t_exec_fn exec_vm_op(t_opcode opcode)
{
	return ((t_exec_fn[OP_COUNT]){
		exec_op_wait,
		exec_op_command,
		exec_op_exec,
		exec_op_arg,
		exec_op_filename,
		exec_op_pipe,
		exec_op_background,
		exec_op_redir_out,
		exec_op_redir_in,
		exec_op_jump,
		exec_op_jump,
		exec_op_wait,
	}[opcode]);
}

static void	vm_run(t_chunk *chunk)
{
	size_t		ip;

	ip = -1UL;
	while (++ip < chunk->len)
		exec_vm_op(chunk->data[ip])(chunk, &ip);
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
			if (arguments_find(&sh->args, "disassemble")->is_set)
				disassemble(&sh->parser.chunk);
			vm_run(&sh->parser.chunk);
		}
		free(line);
	}
	ft_printf("exit\n");
	return (0);
}

t_result	environment_init(t_environment *sh, char **envp)
{
	t_result	result;

	(void)sh;
	ft_vector_init(&sh->public, 64);
	ft_vector_init(&sh->private, 8);
	while (*envp)
	{
		result = ft_vector_push(&sh->public,
				ft_gen_val(TYPE_OTHER, (t_any){.str = ft_strdup(*envp)}));
		if (result != RESULT_OK)
			return (RESULT_ERROR);
		envp++;
	}
	return (RESULT_OK);
}

static void	sh_destroy(t_shell *sh)
{
	arguments_destroy(&sh->args);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		*sh = &g_sh;
	int			exit_code;

	if (arguments_init(&sh->args, argc, argv) != RESULT_OK
		|| environment_init(&sh->env, envp) != RESULT_OK
		|| parser_init(&sh->parser, &sh->lexer) != RESULT_OK
		|| ft_vector_init(&sh->pids, 16) != RESULT_OK)
	{
		sh_destroy(sh);
		return (2);
	}
	sh->prev_fd = 0;
	sh->pipefd[0] = 0;
	sh->pipefd[1] = 1;
	// if (arguments_find_short(&sh->args, 'c')->is_set)
	// 	exit_code = command(&sh, arg);
		exit_code = repl(sh);
	return (exit_code);
}
