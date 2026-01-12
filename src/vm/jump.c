/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:12:21 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 17:13:18 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/bytecode.h"
#include "vm/vm_internal.h"
#include <stdbool.h>
#include <stdint.h>

void	vm_jump(t_vm *vm, t_program *program)
{
	int32_t		jmp_pos;
	t_opcode	op;
	int			exit_code;
	bool		should_jump;

	op = program->data[program->pc++];
	jmp_pos = program_get_i32(program);
	exit_code = (int64_t)vec_get(vm->exit_codes, -1);
	should_jump = (exit_code == 0);
	if (op & JUMP_NEG_BIT)
		should_jump = !should_jump;
	if (should_jump)
		program->pc = (size_t)jmp_pos;
}
