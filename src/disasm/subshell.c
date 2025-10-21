/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 23:37:37 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/20 00:45:06 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"
#include "vm/bytecode.h"

void	disasm_subshell(t_program *program, size_t *offset_ptr)
{
	disasm_print_i32(program, offset_ptr, 1);
	disasm_print_desc("SUBSHELL");
}
