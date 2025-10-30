/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:02:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/23 13:24:13 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "parser/parser.h"
#include "vm/bytecode.h"

t_result	parse_r_out(t_parser *p, t_token t)
{
	t_token	filename;

	if (++p->redirs > MAX_REDIRS)
	{
		print_error(p, t, "Too many redirects");
		return (RESULT_ERROR);
	}
	if (parser_consume(p, TOK_WORD, "Expected valid filename") != RESULT_OK)
		return (RESULT_ERROR);
	filename = p->prev_token;
	if (t.type == TOK_REDIR_APPEND)
		program_write_u8(&p->program, OP_OUT | REDIR_APPEND_BIT);
	else
		program_write_u8(&p->program, OP_OUT);
	program_write_i32(&p->program, t.fd);
	program_write_u16(&p->program, (uint16_t)filename.pos.len);
	program_write_str(&p->program, p->lexer->input + filename.pos.start,
		(size_t)filename.pos.len);
	return (RESULT_OK);
}

t_result	parse_r_in(t_parser *p, t_token t)
{
	t_token	filename;

	if (++p->redirs > MAX_REDIRS)
	{
		print_error(p, t, "Too many redirects");
		return (RESULT_ERROR);
	}
	if (parser_consume(p, TOK_WORD, "Expected valid filename") != RESULT_OK)
		return (RESULT_ERROR);
	filename = p->prev_token;
	program_write_u8(&p->program, OP_IN);
	program_write_i32(&p->program, t.fd);
	program_write_u16(&p->program, (uint16_t)filename.pos.len);
	program_write_str(&p->program, p->lexer->input + filename.pos.start,
		(size_t)filename.pos.len);
	return (RESULT_OK);
}

t_result	parse_heredoc(t_parser *p, t_token t)
{
	t_token	delim;

	if (++p->redirs > MAX_REDIRS)
	{
		print_error(p, t, "Too many redirects");
		return (RESULT_ERROR);
	}
	if (parser_consume(p, TOK_WORD, "Unexpected token") != RESULT_OK)
		return (RESULT_ERROR);
	delim = p->prev_token;
	program_write_u8(&p->program, OP_HEREDOC);
	program_write_i32(&p->program, t.fd);
	program_write_u16(&p->program, (uint16_t)delim.pos.len);
	program_write_str(&p->program, p->lexer->input + delim.pos.start,
		(size_t)delim.pos.len);
	return (RESULT_OK);
}
