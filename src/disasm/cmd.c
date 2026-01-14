/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:20:28 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 14:38:07 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"
#include <stdint.h>

/**
 * @brief Disassembles the CMD instruction.
 *
 * @param program Pointer to the program being disassembled
 * @param offset_ptr Pointer to the current offset in the program
 */
void	disasm_cmd(t_program *program, size_t *offset_ptr)
{
	disasm_print_i32(program, offset_ptr, 1);
	disasm_print_desc("CMD");
}
