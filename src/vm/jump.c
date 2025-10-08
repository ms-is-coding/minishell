/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:12:21 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 21:55:11 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/bytecode.h"
#include "vm/vm_internal.h"
#include "libft.h"
#include <stdint.h>

void	vm_jz(t_vm *vm, t_program *program)
{
	int32_t	jmp_pos;

	program->pc++;
	jmp_pos = program_get_i32(program);
	if (ft_vector_at(&vm->exit_codes, -1).value.i32 != 0)
	{
		program->pc--;
		return ;
	}
	program->pc = (size_t)jmp_pos - 1;
	return ;
}

void	vm_jnz(t_vm *vm, t_program *program)
{
	int32_t	jmp_pos;

	program->pc++;
	jmp_pos = program_get_i32(program);
	if (ft_vector_at(&vm->exit_codes, -1).value.i32 == 0)
	{
		program->pc--;
		return ;
	}
	program->pc = (size_t)jmp_pos - 1;
}
