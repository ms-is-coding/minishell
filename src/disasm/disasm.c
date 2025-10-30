/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:47:14 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/30 08:25:40 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"
#include "disasm/disasm.h"
#include "ansi.h"
#include "vm/bytecode.h"
#include <stddef.h>
#include <stdint.h>

static t_disassembler	disasm_opcode(t_opcode opcode)
{
	if (opcode < 0 || opcode >= OP_COUNT)
		return (NULL);
	return ((t_disassembler[OP_COUNT]){
		[OP_NULL] = disasm_null,
		[OP_SUBSHELL] = disasm_subshell,
		[OP_CMD] = disasm_cmd,
		[OP_ARG] = disasm_arg,
		[OP_EXEC] = disasm_exec,
		[OP_OUT] = disasm_out,
		[OP_IN] = disasm_in,
		[OP_JUMP] = disasm_jump,
		[OP_HEREDOC] = disasm_heredoc,
	}[opcode]);
}

void	disasm(t_program *program)
{
	t_disassembler	handler;
	size_t			offset;

	offset = 0;
	while (offset < program->len)
	{
		handler = disasm_opcode(program->data[offset] & OPCODE_MASK);
		disasm_print_addr(offset);
		disasm_print_opcode(program, &offset);
		if (!handler)
		{
			ft_dprintf(2, ANSI_RED "\nError while disassembling\n" ANSI_RESET);
			return ;
		}
		handler(program, &offset);
	}
}
