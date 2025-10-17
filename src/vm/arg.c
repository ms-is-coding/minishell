/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:04:49 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/17 02:21:14 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander.h"
#include "vm/bytecode.h"
#include "vm/vm_internal.h"
#include "shell.h"
#include <stdint.h>

void	vm_arg_dummy(t_vm *vm, t_program *program)
{
	uint16_t	len;
	t_expander	*exp;

	program->pc++;
	len = program_get_u16(program);
	exp = &((t_shell *)vm->shell)->expander;
	expander_setup(exp, &vm->frame,
		(char *)program->data + program->pc, len);
	expander_expand(exp, VEXPM_COUNT);
	program->pc += len;
}

void	vm_arg(t_vm *vm, t_program *program)
{
	uint16_t	len;
	t_expander	*exp;

	program->pc++;
	len = program_get_u16(program);
	exp = &((t_shell *)vm->shell)->expander;
	expander_setup(exp, &vm->frame,
		(char *)program->data + program->pc, len);
	expander_expand(exp, VEXPM_PREPARE);
	expander_setup(exp, &vm->frame,
		(char *)program->data + program->pc, len);
	expander_expand(exp, VEXPM_EXTRACT);
	program->pc += len;
}
