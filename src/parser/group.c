/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:21:08 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/13 19:56:22 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "vm/bytecode.h"
#include "core/string.h"

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

	(void)token;
	result = parser_parse_expr(p, PREC_NUL);
	if (result != RESULT_OK)
		return (result);
	result = parser_consume(p, TOK_PAREN_CLOSE, "Expected ')'");
	return (result);
}
