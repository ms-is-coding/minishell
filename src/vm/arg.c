/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:04:49 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 16:28:05 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander.h"
#include "vm/bytecode.h"
#include "vm/vm_internal.h"
#include "shell.h"
#include <stdint.h>

/**
 * @brief Dummy argument handler that only counts the number of arguments.
 *
 * @param vm Pointer to the virtual machine
 * @param program Pointer to the program being executed
 */
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

/**
 * @brief Actual argument handler that expands and extracts arguments.
 *
 * @param vm Pointer to the virtual machine
 * @param program Pointer to the program being executed
 */
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
