/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:20:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 22:56:18 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"
#include <stdint.h>

void	disasm_cmd(t_program *program, size_t *offset_ptr)
{
	int32_t	argv;

	argv = disasm_print_i32(program, offset_ptr, 1);
	(void)argv;
	disasm_print_desc("CMD");
}
