/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 00:41:34 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:42:06 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/vector.h"
#include "vm/bytecode.h"
#include "vm/vm_internal.h"
#include "core/stdio.h"

/**
 * @brief Executes a command in the virtual machine.
 *
 * @param vm Pointer to the virtual machine instance
 * @param program Pointer to the program being executed
 */
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
	vm_spawn(vm);
	if (op & EXEC_WAIT_BIT)
	{
		vm_wait(vm, program);
		vec_clear(vm->pids);
	}
	vm->frame.argc = 0;
}
