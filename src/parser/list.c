/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:20:21 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 22:29:55 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

t_result	parse_semi(t_parser *p, t_token token)
{
	if (p->curr_token.type == TOK_EOF
		|| p->curr_token.type == TOK_PAREN_CLOSE)
		return (RESULT_OK);
	program_write_u8(&p->program, OP_WAIT);
	return (parser_parse_expr(p, parser_get_rule(token.type).precedence));
}
