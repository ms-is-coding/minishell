/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:03:47 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 16:56:05 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "parser/parser.h"
#include "vm/bytecode.h"

t_result	parse_error(t_parser *p, t_token token)
{
	print_error(p, token, "Unterminated string");
	return (RESULT_ERROR);
}

t_result	parse_pipe(t_parser *p, t_token token)
{
	if ((p->program.data[p->program.len - 1] & OPCODE_MASK) == OP_EXEC)
		p->program.data[p->program.len - 1] = OP_EXEC | EXEC_PIPELINE_BIT;
	else
		program_write_u8(&p->program, OP_EXEC | EXEC_PIPELINE_BIT);
	return (parser_parse_expr(p, parser_get_rule(token.type).precedence));
}

t_result	parser_parse(t_parser *p, char *line)
{
	t_result	result;

	lexer_init(p->lexer, line);
	parser_init(p, p->lexer);
	parser_advance(p);
	while (p->curr_token.type != TOK_EOF)
	{
		result = parser_parse_expr(p, PREC_NUL);
		if (result != RESULT_OK)
			return (result);
	}
	return (RESULT_OK);
}
