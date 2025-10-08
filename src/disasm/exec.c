/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:28:44 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 22:50:32 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"

void	disasm_exec(t_program *program, size_t *offset_ptr)
{
	(void)program;
	(void)offset_ptr;
	disasm_print_desc("EXEC");
}
