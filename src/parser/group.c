/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:21:08 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/15 11:59:09 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

/**
 * @brief Parses a grouped expression enclosed in parentheses.
 *
 * @param p Pointer to the parser structure
 * @param token The opening parenthesis token
 * @return Result of the parsing operation.
 */
t_result	parse_group(t_parser *p, t_token token)
{
	t_result	result;

	if (p->mode == PARSER_MODE_PIPE)
	{
		print_error(p, token, "Parentheses cannot be used inside pipelines or"\
			" redirections");
		return (RESULT_ERROR);
	}
	p->mode = PARSER_MODE_GROUP;
	result = parser_parse_expr(p, PREC_NUL);
	if (result != RESULT_OK)
		return (result);
	result = parser_consume(p, TOK_PAREN_CLOSE, "Expected ')'");
	return (result);
}
