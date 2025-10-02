/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:18:40 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 16:35:27 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"
#include <stdlib.h>

static t_exec_handler	dispatch_opcode(t_opcode opcode)
{
	if (opcode < 0 || opcode >= OP_COUNT)
		return (NULL);
	return ((t_exec_handler[OP_COUNT]){
		[OP_NULL] = exec_wait,
		[OP_CMD] = exec_command,
		[OP_EXE] = exec_exec,
		[OP_ARG] = exec_arg,
		[OP_FNAME] = exec_filename,
		[OP_PIPE] = exec_pipe,
		[OP_BG] = exec_background,
		[OP_OUT] = exec_redir_out,
		[OP_IN] = exec_redir_in,
		[OP_JZ] = exec_jump,
		[OP_JNZ] = exec_jump,
		[OP_WAIT] = exec_wait,
	}[opcode]);
}

int	vm_run(t_vm *vm, t_program *program)
{
	t_exec_handler	handler;

	program->pc = 0UL;
	while (program->pc < program->len)
	{
		handler = dispatch_opcode(program->data[program->pc]);
		if (!handler)
		{
			ft_printf("FATAL: SIGILL\n");
			exit(0);
		}
		handler(vm, program);
		program->pc++;
	}
	return (0);
}
