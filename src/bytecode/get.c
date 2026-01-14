/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:14:55 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 15:24:23 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"
#include "vm/bytecode.h"
#include <stdint.h>

/**
 * @brief Reads a 16-bit unsigned integer from the program's bytecode at the
 * current program counter and advances it.
 *
 * @param program Pointer to the program structure
 * @return The 16-bit unsigned integer read from the bytecode.
 */
uint16_t	program_get_u16(t_program *program)
{
	uint16_t	val;

	ft_memcpy(&val, &program->data[program->pc], sizeof(uint16_t));
	program->pc += sizeof(uint16_t);
	return (val);
}

/**
 * @brief Reads a 32-bit integer from the program's bytecode at the current
 * program counter and advances it.
 *
 * @param program Pointer to the program structure
 * @return The 32-bit integer read from the bytecode.
 */
int32_t	program_get_i32(t_program *program)
{
	int32_t	val;

	ft_memcpy(&val, &program->data[program->pc], sizeof(int32_t));
	program->pc += sizeof(int32_t);
	return (val);
}
