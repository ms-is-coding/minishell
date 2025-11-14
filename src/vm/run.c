/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:18:40 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/06 18:07:03 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm/vm_internal.h"
#include "common.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static t_exec_handler	dispatch_opcode(t_opcode opcode)
{
	if (opcode < 0 || opcode >= OP_COUNT)
		return (NULL);
	return ((t_exec_handler[OP_COUNT]){
		[OP_SUBSHELL] = vm_subshell,
		[OP_CMD] = vm_command,
		[OP_ARG] = vm_arg,
		[OP_EXEC] = vm_exec,
		[OP_OUT] = vm_redir_out,
		[OP_IN] = vm_redir_in,
		[OP_JUMP] = vm_jump,
		[OP_HEREDOC] = vm_heredoc,
	}[opcode]);
}

void	vm_run(t_vm *vm, t_program *program)
{
	t_exec_handler	handler;

	vm->prev_fd = 0;
	vm->pipe_fd[STDIN_FILENO] = STDIN_FILENO;
	vm->pipe_fd[STDOUT_FILENO] = STDOUT_FILENO;
	program->pc = 0UL;
	ft_vector_init(&vm->pids, 16);
	vm->active = true;
	vm->redir_count = 0;
	while (program->pc < program->len)
	{
		handler = dispatch_opcode(program->data[program->pc] & OPCODE_MASK);
		if (!handler)
		{
			ft_printf("FATAL: SIGILL (%02hhx) at %lx\n",
				program->data[program->pc], program->pc);
			exit(128 + SIGILL);
		}
		handler(vm, program);
	}
	ft_vector_free(&vm->pids);
	vm->active = false;
}

void	vm_run_range(t_vm *vm, t_program *program,
			size_t end)
{
	t_exec_handler	handler;

	vm->prev_fd = 0;
	vm->pipe_fd[STDIN_FILENO] = STDIN_FILENO;
	vm->pipe_fd[STDOUT_FILENO] = STDOUT_FILENO;
	ft_vector_init(&vm->pids, 16);
	vm->active = true;
	vm->here_doc = false;
	vm->redir_count = 0;
	while (program->pc < end)
	{
		handler = dispatch_opcode(program->data[program->pc] & OPCODE_MASK);
		if (!handler)
		{
			ft_printf("FATAL: SIGILL (%02hhx) at %lx\n",
				program->data[program->pc], program->pc);
			exit(128 + SIGILL);
		}
		handler(vm, program);
	}
	ft_vector_free(&vm->pids);
	vm->active = false;
}
