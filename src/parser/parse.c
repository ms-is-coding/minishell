/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:03:47 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/05 23:59:24 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/parser.h"
#include "token.h"

t_result	parse_error(t_parser *p, t_token token)
{
	(void)p;
	(void)token;
	ft_printf("Error\n");
	print_token(token);
	return (RESULT_ERROR);
}

t_result	parse_pipe(t_parser *p, t_token token)
{
	p->program.data[p->program.len - 1] = OP_PIPE;
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
	program_write_u8(&p->program, OP_WAIT);
	return (RESULT_OK);
}
