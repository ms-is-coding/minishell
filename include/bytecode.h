/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:07:16 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/01 21:53:21 by smamalig         ###   ########.fr       */
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
	OP_COMMAND,
	OP_EXEC,
	OP_ARG,
	OP_FILENAME,
	OP_PIPE,
	OP_BACKGROUND,
	OP_REDIR_OUT,
	OP_REDIR_IN,
	OP_JZ,
	OP_JNZ,
	OP_WAIT,
	OP_COUNT,
}	t_opcode;

typedef struct s_chunk
{
	uint8_t	data[MAX_CHUNK];
	size_t	len;
}	t_chunk;

t_result	chunk_write_u8(t_chunk *chunk, uint8_t data);
t_result	chunk_write_i32(t_chunk *chunk, int32_t data);
t_result	chunk_write_str(t_chunk *chunk, const char *data, size_t len);

#endif
