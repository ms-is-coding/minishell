/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:15:14 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 14:45:07 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"
#include "core/stdio.h"
#include "ansi.h"
#include "vm/bytecode.h"
#include "core/string.h"
#include <stdint.h>

/**
 * @brief Prints a specified number of bytes from the program data.
 *
 * @param program Pointer to the program containing the data
 * @param offset Pointer to the current offset in the program data
 * @param count Number of bytes to print
 * @param start Starting index for formatting
 */
static void	print_bytes(t_program *program, size_t *offset, int count,
	int start)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (((i + start) & 7) == 0)
		{
			ft_printf("\n%8.0i", 0);
		}
		ft_printf("%02x ", program->data[(*offset)++]);
	}
}

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
 * @brief Prints the opcode in the disassembly output with color coding.
 *
 * @param program Pointer to the program containing the opcode
 * @param offset Pointer to the current offset in the program data
 */
void	disasm_print_opcode(t_program *program, size_t *offset)
{
	t_opcode	opcode;

	opcode = program->data[(*offset)++];
	if (opcode & 0x80)
		ft_printf(ANSI_BOLD ANSI_BLUE "%02x " ANSI_RESET, opcode);
	else if (opcode & 0x40)
		ft_printf(ANSI_BLUE "%02x " ANSI_RESET, opcode);
	else
		ft_printf(ANSI_CYAN "%02x " ANSI_RESET, opcode);
}

/**
 * @brief Prints a 32-bit integer from the program data with color coding.
 *
 * @param program Pointer to the program containing the data
 * @param offset_ptr Pointer to the current offset in the program data
 * @param start Starting index for formatting
 * @return The 32-bit integer read from the program data
 */
int32_t	disasm_print_i32(t_program *program, size_t *offset_ptr, int start)
{
	int32_t	ret;

	ft_printf(ANSI_MAGENTA);
	ft_memcpy(&ret, &program->data[*offset_ptr], sizeof(int32_t));
	print_bytes(program, offset_ptr, 4, start);
	ft_printf(ANSI_RESET);
	return (ret);
}

/**
 * @brief Prints a 16-bit unsigned integer from the program data with color coding.
 *
 * @param program Pointer to the program containing the data
 * @param offset_ptr Pointer to the current offset in the program data
 * @param start Starting index for formatting
 * @return The 16-bit unsigned integer read from the program data
 */
uint16_t	disasm_print_u16(t_program *program, size_t *offset_ptr, int start)
{
	uint16_t	ret;

	ft_printf(ANSI_GREEN);
	ft_memcpy(&ret, &program->data[*offset_ptr], sizeof(uint16_t));
	print_bytes(program, offset_ptr, 2, start);
	ft_printf(ANSI_RESET);
	return (ret);
}

/**
 * @brief Prints a string of specified length from the program data with color coding.
 *
 * @param program Pointer to the program containing the data
 * @param offset_ptr Pointer to the current offset in the program data
 * @param len Length of the string to print
 * @param start Starting index for formatting
 */
void	disasm_print_str(t_program *program, size_t *offset_ptr,
	uint16_t len, int start)
{
	ft_printf(ANSI_RED);
	print_bytes(program, offset_ptr, len, start);
	ft_printf(ANSI_RESET);
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
