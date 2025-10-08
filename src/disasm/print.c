/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:15:14 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 22:57:14 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "disasm/disasm_internal.h"
#include "libft_printf.h"
#include "ansi.h"
#include "vm/bytecode.h"
#include <stdint.h>
#include <wchar.h>

static void	print_bytes(t_program *program, size_t *offset, int count, int start)
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

void	disasm_print_addr(size_t offset)
{
	ft_printf(ANSI_YELLOW " %5lx" ANSI_RESET ": ", offset);
}

void	disasm_print_opcode(t_program *program, size_t *offset)
{
	t_opcode	opcode;

	opcode = program->data[(*offset)++];
	if (opcode == (opcode & OPCODE_MASK))
		ft_printf(ANSI_CYAN "%02x " ANSI_RESET, opcode);
	else
		ft_printf(ANSI_BLUE "%02x " ANSI_RESET, opcode);
}

int32_t	disasm_print_i32(t_program *program, size_t *offset_ptr, int start)
{
	int32_t	ret;

	ft_printf(ANSI_MAGENTA);
	ft_memcpy(&ret, &program->data[*offset_ptr], sizeof(int32_t));
	print_bytes(program, offset_ptr, 4, start);
	ft_printf(ANSI_RESET);
	return (ret);
}

uint16_t	disasm_print_u16(t_program *program, size_t *offset_ptr, int start)
{
	uint16_t	ret;

	ft_printf(ANSI_GREEN);
	ft_memcpy(&ret, &program->data[*offset_ptr], sizeof(uint16_t));
	print_bytes(program, offset_ptr, 2, start);
	ft_printf(ANSI_RESET);
	return (ret);
}

void	disasm_print_str(t_program *program, size_t *offset_ptr,
	uint16_t len, int start)
{
	ft_printf(ANSI_RED);
	print_bytes(program, offset_ptr, len, start);
	ft_printf(ANSI_RESET);
}

void	disasm_print_desc(const char *desc)
{
	ft_printf("\033[35G%s\n", desc);
}
