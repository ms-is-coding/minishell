/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:04:49 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/11 16:20:00 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"
#include "shell.h"

void	vm_arg(t_vm *vm, t_program *program)
{
	uint16_t	len;

	program->pc++;
	len = program_get_u16(program);
	expander_expand(
		&((t_shell *)vm->shell)->expander,
		&vm->frame,
		(char *)program->data + program->pc,
		len);
	program->pc += len;
}
