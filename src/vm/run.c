/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:18:40 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 13:56:19 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static t_exec_handler	dispatch_opcode(t_opcode opcode)
{
	if (opcode < 0 || opcode >= OP_COUNT)
		return (NULL);
	return ((t_exec_handler[OP_COUNT]){
		[OP_NULL] = vm_wait,
		[OP_CMD] = vm_command,
		[OP_EXE] = vm_exec,
		[OP_ARG] = vm_arg,
		[OP_FNAME] = vm_filename,
		[OP_PIPE] = vm_pipe,
		[OP_OUT] = vm_redir_out,
		[OP_IN] = vm_redir_in,
		[OP_JZ] = vm_jz,
		[OP_JNZ] = vm_jnz,
		[OP_WAIT] = vm_wait,
	}[opcode]);
}

int	vm_run(t_vm *vm, t_program *program)
{
	t_exec_handler	handler;

	vm->prev_fd = 0;
	vm->pipe_fd[STDIN_FILENO] = STDIN_FILENO;
	vm->pipe_fd[STDOUT_FILENO] = STDOUT_FILENO;
	program->pc = 0UL;
	ft_vector_init(&vm->pids, 16);
	while (program->pc < program->len)
	{
		handler = dispatch_opcode(program->data[program->pc]);
		if (!handler)
		{
			ft_printf("FATAL: SIGILL (%02hhx)\n", program->data[program->pc]);
			exit(128 + SIGILL);
		}
		handler(vm, program);
		program->pc++;
	}
	ft_vector_free(&vm->pids);
	return (0);
}
