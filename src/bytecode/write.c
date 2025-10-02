/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:05:04 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/02 09:28:52 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bytecode.h"

t_result	chunk_write_u8(t_chunk *chunk, uint8_t data)
{
	if (chunk->len + sizeof(uint8_t) >= MAX_CHUNK)
		return (RESULT_ERROR);
	chunk->data[chunk->len++] = data;
	return (RESULT_OK);
}

t_result	chunk_write_i32(t_chunk *chunk, int32_t data)
{
	if (chunk->len + sizeof(int32_t) >= MAX_CHUNK)
		return (RESULT_ERROR);
	ft_memcpy(chunk->data + chunk->len, &data, sizeof(int32_t));
	chunk->len += sizeof(int32_t);
	return (RESULT_OK);
}

t_result	chunk_write_str(t_chunk *chunk, const char *data, size_t len)
{
	if (chunk->len + len >= MAX_CHUNK)
		return (RESULT_ERROR);
	ft_memcpy(chunk->data + chunk->len, data, len);
	chunk->len += len;
	return (RESULT_OK);
}
