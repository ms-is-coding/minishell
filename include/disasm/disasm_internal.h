/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:05:07 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 17:41:50 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_INTERNAL_H
# define DISASM_INTERNAL_H

# include "vm/bytecode.h"

typedef void	(*t_disassembler)(
	t_program *program, size_t *offset_ptr);

void		disasm_print_addr(size_t offset);
void		disasm_print_opcode(t_program *program, size_t *offset_ptr);
int32_t		disasm_print_i32(t_program *program, size_t *offset_ptr, int start);
uint16_t	disasm_print_u16(t_program *program, size_t *offset_ptr, int start);
void		disasm_print_desc(const char *desc);
void		disasm_print_str(t_program *program, size_t *offset_ptr,
				uint16_t len, int start);

void		disasm_null(t_program *program, size_t *offset_ptr);
void		disasm_cmd(t_program *program, size_t *offset_ptr);
void		disasm_arg(t_program *program, size_t *offset_ptr);
void		disasm_exec(t_program *program, size_t *offset_ptr);
void		disasm_out(t_program *program, size_t *offset_ptr);
void		disasm_in(t_program *program, size_t *offset_ptr);
void		disasm_jump(t_program *program, size_t *offset_ptr);
void		disasm_heredoc(t_program *program, size_t *offset_ptr);

#endif // DISASM_INTERNAL_H
