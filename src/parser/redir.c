/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:02:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/03 22:06:28 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

t_result	parse_r_out(t_parser *p, t_token t)
{
	t_token	filename;

	if (parser_consume(p, TOK_WORD, "Expected valid filename") != RESULT_OK)
		return (RESULT_ERROR);
	filename = p->prev_token;
	program_write_u8(&p->program, OP_OUT);
	program_write_i32(&p->program, t.fd);
	program_write_u8(&p->program, OP_FNAME);
	program_write_u8(&p->program, (unsigned char)filename.pos.len);
	program_write_str(&p->program, p->lexer->input + filename.pos.start,
		(size_t)filename.pos.len);
	return (RESULT_OK);
}
