/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:33:39 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 22:59:14 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"

void	disasm_jz(t_program *program, size_t *offset_ptr)
{
	(void)program;
	(void)offset_ptr;
	disasm_print_i32(program, offset_ptr, 1);
	disasm_print_desc("JZ");
}

void	disasm_jnz(t_program *program, size_t *offset_ptr)
{
	(void)program;
	(void)offset_ptr;
	disasm_print_i32(program, offset_ptr, 1);
	disasm_print_desc("JNZ");
}
