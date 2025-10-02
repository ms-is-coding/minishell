/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:10:56 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 00:32:07 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_result	parse_command(t_parser *p, t_token token)
{
	if (p->in_cmd)
	{
		chunk_write_u8(&p->chunk, OP_ARG);
		chunk_write_u8(&p->chunk, (unsigned char)token.pos.len);
		chunk_write_str(&p->chunk, p->lexer->input + token.pos.start,
			token.pos.len);
		return (RESULT_OK);
	}
	chunk_write_u8(&p->chunk, OP_COMMAND);
	chunk_write_u8(&p->chunk, (unsigned char)token.pos.len);
	chunk_write_str(&p->chunk, p->lexer->input + token.pos.start,
		token.pos.len);
	while (p->curr_token.type == TOK_WORD
		|| p->curr_token.type == TOK_REDIR_OUT)
	{
		p->in_cmd = true;
		if (parser_parse_expr(p, PREC_REDIR) != RESULT_OK)
			return (RESULT_ERROR);
	}
	chunk_write_u8(&p->chunk, OP_EXEC);
	p->in_cmd = false;
	return (RESULT_OK);
}

t_result	parse_subcommand(t_parser *p, t_token t)
{
	t_result	result;

	result = parse_command(p, t);
	parser_consume(p, TOK_PAREN_CLOSE, "Expected )");
	return (result);
}
