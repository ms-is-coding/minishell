/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:10:56 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 23:35:44 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include <stddef.h>

static t_result	parse_command(t_parser *p, t_token t)
{
	size_t	pos;

	p->argc = 0;
	program_write_u8(&p->program, OP_CMD);
	pos = p->program.len;
	program_write_i32(&p->program, 0);
	p->in_cmd = true;
	parse_word(p, t);
	while (p->curr_token.type == TOK_WORD
		|| p->curr_token.type == TOK_REDIR_OUT)
		if (parser_parse_expr(p, PREC_REDIR) != RESULT_OK)
			return (RESULT_ERROR);
	program_write_u8(&p->program, OP_EXE);
	ft_memcpy(p->program.data + pos, &p->argc, sizeof(int32_t));
	p->in_cmd = false;
	return (RESULT_OK);
}

t_result	parse_word(t_parser *p, t_token token)
{
	if (!p->in_cmd)
		return (parse_command(p, token));
	program_write_u8(&p->program, OP_ARG);
	program_write_u8(&p->program, (unsigned char)token.pos.len);
	program_write_str(&p->program, p->lexer->input + token.pos.start,
		(size_t)token.pos.len);
	p->argc++;
	return (RESULT_OK);
}
