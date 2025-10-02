/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:21:08 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 17:02:33 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

t_result	parse_group(t_parser *p, t_token token)
{
	t_result	result;

	(void)token;
	result = parser_parse_expr(p, PREC_NUL);
	parser_consume(p, TOK_PAREN_CLOSE, "Expected ')'");
	return (result);
}
