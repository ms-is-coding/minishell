/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:02:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 00:33:25 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_result	parse_r_out(t_parser *p, t_token t)
{
	t_token	filename;

	filename = parser_consume(p, TOK_WORD, "Expected valid filename");
	chunk_write_u8(&p->chunk, OP_FILENAME);
	chunk_write_u8(&p->chunk, (unsigned char)filename.pos.len);
	chunk_write_str(&p->chunk, p->lexer->input + filename.pos.start,
		filename.pos.len);
	chunk_write_u8(&p->chunk, OP_REDIR_OUT);
	chunk_write_i32(&p->chunk, t.fd);
	return (RESULT_OK);
}
