/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:04:49 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 22:32:36 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"

/*
static void	exec_op_arg(t_program *program, size_t *ip)
{
	t_stack_frame	*frame;
	size_t			len;

	frame = frames;
	len = program->data[++(*ip)];
	frame->stack[frame->sp++] = ft_strndup((char *)program->data + *ip + 1, len);
	*ip += len;
}
*/

void	vm_arg(t_vm *vm, t_program *program)
{
	// todo
	(void)vm;
	(void)program;
}
