/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:32:47 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/11 16:11:21 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/bytecode.h"
#include "vm/vm_internal.h"
#include "allocator/allocator.h"

void	vm_command(t_vm *vm, t_program *program)
{
	int32_t	argc;

	program->pc++;
	argc = program_get_i32(program);
	vm->frame.argc = argc;
	vm->frame.capacity = argc;
	vm->frame.i = 0;
	vm->frame.arena = allocator_arena_new(vm->allocator);
	if (!vm->frame.arena)
		exit(-1);
	vm->frame.argv = allocator_alloc(vm->allocator, sizeof(char *)
			* ((unsigned)vm->frame.argc + 1), vm->frame.arena).data;
}
