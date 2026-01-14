/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:13:35 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 15:25:59 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"

/**
 * @brief Disassembles a NULL operation.
 *
 * @param program Pointer to the program being disassembled
 * @param offset_ptr Pointer to the current offset in the program
 * @note The parameters are marked as unused to avoid compiler warnings.
 */
void	disasm_null(
	__attribute__((unused)) t_program *program,
	__attribute__((unused)) size_t *offset_ptr)
{
	disasm_print_desc("NULL");
}
