/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:13:35 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 22:49:39 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"

void	disasm_null(t_program *program, size_t *offset_ptr)
{
	(void)program;
	(void)offset_ptr;
	disasm_print_desc("NULL");
}
