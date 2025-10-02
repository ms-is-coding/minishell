/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:10:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 22:20:44 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"

/*
static void exec_op_exec(t_program *program, size_t *ip)
{
	t_stack_frame	*frame;
	char			*exec;
	t_builtin_fn	builtin;
	int				pid;

	env = malloc(sizeof(char *) * (g_sh.env.public.length + 1));
	if (!env)
		return ;
	ft_vector_foreach(&g_sh.env.public, push_env);
	env[g_sh.env.public.length] = NULL;
	frame = frames;
	frame->stack[frame->sp++] = NULL;
	builtin = find_builtin(frame->stack[0]);
	if (builtin == builtin_exec || builtin == builtin_exit)
	{
		builtin(&g_sh, (int)frame->sp - 1, frame->stack);
		exit(0);
	}
	pid = fork();
	if (pid == 0)
	{
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
	(void)program;
	(void)ip;
}
*/

void	vm_exec(t_vm *vm, t_program *program)
{
	// todo
	(void)vm;
	(void)program;
}
