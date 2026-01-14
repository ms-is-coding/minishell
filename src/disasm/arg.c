/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:27:35 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 14:36:12 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"
#include <stdint.h>

/**
 * @brief Disassembles the ARG instruction.
 *
 * @param program Pointer to the program being disassembled
 * @param offset_ptr Pointer to the current offset in the program
 */
void	disasm_arg(t_program *program, size_t *offset_ptr)
{
	uint16_t	len;

	len = disasm_print_u16(program, offset_ptr, 1);
	disasm_print_str(program, offset_ptr, len, 3);
	disasm_print_desc("ARG");
}
