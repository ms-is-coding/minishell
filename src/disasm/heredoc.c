/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 08:15:08 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/30 08:26:18 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm/disasm_internal.h"

void	disasm_heredoc(t_program *program, size_t *offset_ptr)

{	
	uint16_t	len;

	disasm_print_i32(program, offset_ptr, 1);
	len = disasm_print_u16(program, offset_ptr, 1);
	disasm_print_str(program, offset_ptr, len, 7);
	disasm_print_desc("HERE-DOC");
}
