/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:28:44 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/20 00:00:21 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"
#include "vm/bytecode.h"

void	disasm_exec(t_program *program, size_t *offset_ptr)
{
	(void)program;
	(void)offset_ptr;
	if (program->data[*offset_ptr - 1] & EXEC_PIPELINE_BIT)
		disasm_print_desc("EXEC (pipe)");
	else if (program->data[*offset_ptr - 1] & EXEC_WAIT_BIT)
		disasm_print_desc("EXEC (wait)");
	else
		disasm_print_desc("EXEC");
}
