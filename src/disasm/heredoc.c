/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 08:15:08 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:45:26 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"

/**
 * @brief Disassembles a heredoc operation.
 *
 * @param program Pointer to the program being disassembled
 * @param offset_ptr Pointer to the current offset in the program
 */
void	disasm_heredoc(t_program *program, size_t *offset_ptr)
{	
	uint16_t	len;

	disasm_print_i32(program, offset_ptr, 1);
	len = disasm_print_u16(program, offset_ptr, 1);
	disasm_print_str(program, offset_ptr, len, 7);
	disasm_print_desc("HERE-DOC");
}
