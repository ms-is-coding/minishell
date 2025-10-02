/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:12:21 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 22:15:55 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"
#include "libft.h"
#include <stdint.h>

void	vm_jz(t_vm *vm, t_program *program)
{
	int32_t	jmp_pos;

	if (ft_vector_at(&vm->exit_codes, -1).value.i32 != 0)
		return ;
	ft_memcpy(&jmp_pos, program->data + program->pc + 1, sizeof(int32_t));
	program->pc = jmp_pos - 1;
}

void	vm_jnz(t_vm *vm, t_program *program)
{
	int32_t	jmp_pos;

	if (ft_vector_at(&vm->exit_codes, -1).value.i32 == 0)
		return ;
	ft_memcpy(&jmp_pos, program->data + program->pc + 1, sizeof(int32_t));
	program->pc = jmp_pos - 1;
}
