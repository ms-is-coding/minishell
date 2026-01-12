/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:21:08 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/12 16:06:34 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "vm/bytecode.h"
#include "core/string.h"

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
