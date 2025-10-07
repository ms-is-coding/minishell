/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:47:14 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 00:57:35 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm.h"
#include <assert.h>
#include <stddef.h>

#define MAX_OFFSET 16

static void print_bytes(int bytes, t_program *program, size_t *offset, const char *desc)
{
	int	i;

	i = -1;
	while (++i < bytes)
	{
		ft_printf("%02x ", program->data[(*offset)++]);
		if (((i - 7) & 7) == 0)
			ft_printf("\n\t\t");
	}
	i = bytes - 1;
	while (++i < MAX_OFFSET)
		ft_printf("   ");
	ft_printf("%s\n", desc);
}

void	disasm(t_program *program)
{
	size_t	len;

	for (size_t offset = 0; offset < program->len;)
	{
		ft_printf("%8lx:\t", offset);
		switch (program->data[offset])
		{
			case OP_NULL:
				print_bytes(1, program, &offset, "NULL");
			break ;
			case OP_EXE:
				print_bytes(1, program, &offset, "EXEC");
			break ;
			case OP_CMD:
				print_bytes(5, program, &offset, "COMMAND");
			break ;
			case OP_ARG:
				len = program->data[offset + 1];
			print_bytes((int)len + 2, program, &offset, "ARG");
			break ;
			case OP_FNAME:
				len = program->data[offset + 1];
			print_bytes((int)len + 2, program, &offset, "FILENAME");
			break ;
			case OP_PIPE:
				print_bytes(1, program, &offset, "PIPE");
			break ;
			case OP_OUT:
				print_bytes(5, program, &offset, "REDIR_OUT");
			break ;
			case OP_JZ:
				print_bytes(5, program, &offset, "JZ");
			break ;
			case OP_JNZ:
				print_bytes(5, program, &offset, "JNZ");
			break ;
			case OP_IN:
				print_bytes(1, program, &offset, "REDIR_IN");
			break ;
			case OP_WAIT:
				print_bytes(1, program, &offset, "WAIT");
			break ;
			default :
				print_bytes(1, program, &offset, "UNKNOWN");
		}
	}
}

/*
void	disassemble(int *program)
{
	size_t	offset;

	offset = -1UL;
	while (++offset < program->len)
	{
		
	}
}
*/
