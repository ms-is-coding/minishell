/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:26:44 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 01:01:00 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BYTECODE_H
# define BYTECODE_H

# include <stddef.h>
# include <stdint.h>

# include "libft.h"

# define MAX_CHUNK 0x10000

typedef enum e_opcode
{
	OP_NULL,
	OP_CMD,
	OP_EXE,
	OP_ARG,
	OP_LONGARG,
	OP_FNAME,
	OP_PIPE,
	OP_OUT,
	OP_IN,
	OP_JZ,
	OP_JNZ,
	OP_WAIT,
	OP_COUNT
}	t_opcode;

typedef struct s_program
{
	uint8_t	data[MAX_CHUNK];
	size_t	len;
	size_t	pc;
}	t_program;

t_result	program_write_u8(t_program *program, uint8_t data);
t_result	program_write_i32(t_program *program, int32_t data);
t_result	program_write_str(t_program *program, const char *data, size_t len);

#endif // BYTECODE_H
