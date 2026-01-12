/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:26:44 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 16:54:50 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BYTECODE_H
# define BYTECODE_H

# include <stddef.h>
# include <stdint.h>

# include "core/stdlib.h"

# define MAX_CHUNK 0x10000

# define OPCODE_MASK 0x3f

# define REDIR_APPEND_BIT 0x80
# define REDIR_FD_BIT 0x40

# define JUMP_NEG_BIT 0x80

# define EXEC_PIPELINE_BIT 0x80
# define EXEC_WAIT_BIT 0x40

typedef enum e_opcode
{
	OP_NULL,
	OP_SUBSHELL,
	OP_CMD,
	OP_ARG,
	OP_EXEC,
	OP_OUT,
	OP_IN,
	OP_JUMP,
	OP_HEREDOC,
	OP_COUNT
}	t_opcode;

typedef struct s_program
{
	uint8_t	data[MAX_CHUNK];
	size_t	len;
	size_t	pc;
}	t_program;

t_result	program_write_u8(t_program *program, uint8_t data);
t_result	program_write_u16(t_program *program, uint16_t data);
t_result	program_write_i32(t_program *program, int32_t data);
t_result	program_write_str(t_program *program, const char *data, size_t len);

uint16_t	program_get_u16(t_program *program);
int32_t		program_get_i32(t_program *program);

#endif // BYTECODE_H
