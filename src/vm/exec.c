/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 00:41:34 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/09 00:46:21 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "vm/bytecode.h"
#include "vm/vm_internal.h"

void	vm_exec(t_vm *vm, t_program *program)
{
	t_opcode	op;

	op = program->data[program->pc++];
	if (op & EXEC_PIPELINE_BIT)
	{
		if (pipe(vm->pipe_fd) < 0)
		{
			ft_printf("pipe failed: %m\n");
			return ;
		}
	}
	vm_spawn(vm, program);
	if (op & EXEC_WAIT_BIT)
	{
		vm_wait(vm, program);
		vm->pids.length = 0;
	}
	vm->frame.i = 0;
}
