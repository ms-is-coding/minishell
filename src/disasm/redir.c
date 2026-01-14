/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:29:54 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 14:52:06 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"
#include <stdint.h>

/**
 * @brief Disassembles an OUT redirection instruction.
 *
 * @param program Pointer to the program being disassembled
 * @param offset_ptr Pointer to the current offset in the program
 */
void	disasm_out(t_program *program, size_t *offset_ptr)

{	
	uint16_t	len;

	disasm_print_i32(program, offset_ptr, 1);
	len = disasm_print_u16(program, offset_ptr, 1);
	disasm_print_str(program, offset_ptr, len, 7);
	disasm_print_desc("OUT");
}

/**
 * @brief Disassembles an IN redirection instruction.
 *
 * @param program Pointer to the program being disassembled
 * @param offset_ptr Pointer to the current offset in the program
 */
void	disasm_in(t_program *program, size_t *offset_ptr)
{
	uint16_t	len;

	disasm_print_i32(program, offset_ptr, 1);
	len = disasm_print_u16(program, offset_ptr, 1);
	disasm_print_str(program, offset_ptr, len, 7);
	disasm_print_desc("IN");
}
