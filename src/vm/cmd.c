/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:32:47 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:41:55 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/bytecode.h"
#include "vm/vm_internal.h"
#include "allocator/allocator.h"
#include "core/stdio.h"
#include <signal.h>

/**
 * @brief Dispatches the opcode to the corresponding handler function.
 *
 * @param opcode The opcode to dispatch
 */
static t_exec_handler	dispatch_opcode(t_opcode opcode)
{
	if (opcode < 0 || opcode >= OP_COUNT)
		return (NULL);
	return ((t_exec_handler[OP_COUNT]){
		[OP_ARG] = vm_arg_dummy,
		[OP_OUT] = vm_redir_dummy,
		[OP_IN] = vm_redir_dummy,
	}[opcode]);
}

/**
 * @brief Counts the number of arguments for a command.
 * @param vm Pointer to the virtual machine
 * @param program Pointer to the program being executed
 * @param argc Number of arguments to count
 * @note If the opcode is invalid, the program will exit with SIGILL.
 */
static void	vm_count(t_vm *vm, t_program *program, int argc)
{
	t_exec_handler	handler;
	int				i;

	i = 0;
	while (i < argc)
	{
		handler = dispatch_opcode(program->data[program->pc] & OPCODE_MASK);
		if (!handler)
		{
			ft_printf("FATAL: SIGILL (%02hhx) at %lx\n",
				program->data[program->pc], program->pc);
			exit(128 + SIGILL);
		}
		handler(vm, program);
		if (handler == vm_arg_dummy)
			i++;
	}
}

/**
 * @brief Handles the command opcode.
 *
 * @param vm Pointer to the virtual machine
 * @param program Pointer to the program being executed
 */
void	vm_command(t_vm *vm, t_program *program)
{
	int32_t	argc;
	size_t	pos;

	program->pc++;
	argc = program_get_i32(program);
	pos = program->pc;
	vm->frame.argc = 0;
	vm->frame.arena = allocator_arena_new(vm->allocator);
	if (!vm->frame.arena)
		exit(-1);
	vm_count(vm, program, argc);
	program->pc = pos;
	vm->frame.argv = allocator_alloc(vm->allocator, sizeof(char *)
			* ((unsigned)vm->frame.argc + 1), vm->frame.arena).data;
	vm->frame.argc = 0;
}
