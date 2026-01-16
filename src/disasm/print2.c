/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:28:39 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/16 17:29:59 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"
#include "core/stdio.h"
#include "ansi.h"
#include <stdint.h>

/**
 * @brief Prints the offset address in the disassembly output.
 *
 * @param offset The offset address to print
 */
void	disasm_print_addr(size_t offset)
{
	ft_printf(ANSI_YELLOW " %5lx" ANSI_RESET ": ", offset);
}

/**
 * @brief Prints the description of the disassembled instruction.
 *
 * @param desc The description string to print
 */
void	disasm_print_desc(const char *desc)
{
	ft_printf("\033[35G%s\n", desc);
}
