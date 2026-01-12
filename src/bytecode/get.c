/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:14:55 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 17:03:29 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"
#include "vm/bytecode.h"
#include <stdint.h>

uint16_t	program_get_u16(t_program *program)
{
	uint16_t	val;

	ft_memcpy(&val, &program->data[program->pc], sizeof(uint16_t));
	program->pc += sizeof(uint16_t);
	return (val);
}

int32_t	program_get_i32(t_program *program)
{
	int32_t	val;

	ft_memcpy(&val, &program->data[program->pc], sizeof(int32_t));
	program->pc += sizeof(int32_t);
	return (val);
}
