/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:05:04 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 16:39:14 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/bytecode.h"

t_result	program_write_u8(t_program *program, uint8_t data)
{
	if (program->len + sizeof(uint8_t) >= MAX_CHUNK)
		return (RESULT_ERROR);
	program->data[program->len++] = data;
	return (RESULT_OK);
}

t_result	program_write_i32(t_program *program, int32_t data)
{
	if (program->len + sizeof(int32_t) >= MAX_CHUNK)
		return (RESULT_ERROR);
	ft_memcpy(program->data + program->len, &data, sizeof(int32_t));
	program->len += sizeof(int32_t);
	return (RESULT_OK);
}

t_result	program_write_str(t_program *program, const char *data, size_t len)
{
	if (program->len + len >= MAX_CHUNK)
		return (RESULT_ERROR);
	ft_memcpy(program->data + program->len, data, len);
	program->len += len;
	return (RESULT_OK);
}
