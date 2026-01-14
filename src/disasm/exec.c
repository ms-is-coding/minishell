/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:28:44 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 15:26:44 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"
#include "vm/bytecode.h"

/**
 * @brief Disassembles the EXEC opcode.
 *
 * @param program Pointer to the program being disassembled
 * @param offset_ptr Pointer to the current offset in the program
 * @note The parameters are marked as unused to avoid compiler warnings.
 */
void	disasm_exec(
	__attribute__((unused)) t_program *program,
	__attribute__((unused)) size_t *offset_ptr)
{
	if (program->data[*offset_ptr - 1] & EXEC_PIPELINE_BIT)
		disasm_print_desc("EXEC (pipe)");
	else if (program->data[*offset_ptr - 1] & EXEC_WAIT_BIT)
		disasm_print_desc("EXEC (wait)");
	else
		disasm_print_desc("EXEC");
}
