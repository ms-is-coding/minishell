/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:33:39 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 15:27:44 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"

/**
 * @brief Disassembles a JUMP operation.
 *
 * @param program Pointer to the program being disassembled
 * @param offset_ptr Pointer to the current offset in the program
 * @note The parameters are marked as unused to avoid compiler warnings.
 */
void	disasm_jump(
	__attribute__((unused)) t_program *program,
	__attribute__((unused)) size_t *offset_ptr)
{
	disasm_print_i32(program, offset_ptr, 1);
	disasm_print_desc("JUMP");
}
