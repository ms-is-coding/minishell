/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:20:21 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 00:32:46 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_result	parse_background(t_parser *p, t_token token)
{
	chunk_write_u8(&p->chunk, OP_BACKGROUND);
	if (p->curr_token.type == TOK_EOF
		|| p->curr_token.type == TOK_PAREN_CLOSE)
		return (RESULT_OK);
	return (parser_parse_expr(p, parser_get_rule(token.type).precedence));
}

t_result	parse_semi(t_parser *p, t_token token)
{
	if (p->curr_token.type == TOK_EOF
		|| p->curr_token.type == TOK_PAREN_CLOSE)
		return (RESULT_OK);
	chunk_write_u8(&p->chunk, OP_WAIT);
	return (parser_parse_expr(p, parser_get_rule(token.type).precedence));
}
