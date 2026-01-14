/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:05:04 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/13 19:53:25 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/bytecode.h"
#include "core/string.h"

/**
 * @brief Writes an 8-bit unsigned integer to the program bytecode.
 *
 * @param program Pointer to the program structure
 * @param data 8-bit unsigned integer to write
 * @return RESULT_OK on success, RESULT_ERROR on failure.
 */
t_result	program_write_u8(t_program *program, uint8_t data)
{
	if (program->len + sizeof(uint8_t) >= MAX_CHUNK)
		return (RESULT_ERROR);
	program->data[program->len++] = data;
	return (RESULT_OK);
}

/**
 * @brief Writes a 16-bit unsigned integer to the program bytecode.
 *
 * @param program Pointer to the program structure
 * @param data 16-bit unsigned integer to write
 * @return RESULT_OK on success, RESULT_ERROR on failure.
 */
t_result	program_write_u16(t_program *program, uint16_t data)
{
	if (program->len + sizeof(uint16_t) >= MAX_CHUNK)
		return (RESULT_ERROR);
	ft_memcpy(program->data + program->len, &data, sizeof(uint16_t));
	program->len += sizeof(uint16_t);
	return (RESULT_OK);
}

/**
 * @brief Writes a 32-bit signed integer to the program bytecode.
 *
 * @param program Pointer to the program structure
 * @param data 32-bit signed integer to write
 * @return RESULT_OK on success, RESULT_ERROR on failure.
 */
t_result	program_write_i32(t_program *program, int32_t data)
{
	if (program->len + sizeof(int32_t) >= MAX_CHUNK)
		return (RESULT_ERROR);
	ft_memcpy(program->data + program->len, &data, sizeof(int32_t));
	program->len += sizeof(int32_t);
	return (RESULT_OK);
}

/**
 * @brief Writes a string to the program bytecode.
 *
 * @param program Pointer to the program structure
 * @param data String to write
 * @param len Length of the string
 * @return RESULT_OK on success, RESULT_ERROR on failure.
 */
t_result	program_write_str(t_program *program, const char *data, size_t len)
{
	if (program->len + len >= MAX_CHUNK)
		return (RESULT_ERROR);
	ft_memcpy(program->data + program->len, data, len);
	program->len += len;
	return (RESULT_OK);
}
