/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:32:47 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 17:30:08 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/bytecode.h"
#include "vm/vm_internal.h"
#include "allocator/allocator.h"
#include "core/stdio.h"
#include <signal.h>

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
