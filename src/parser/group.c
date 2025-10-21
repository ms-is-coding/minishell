/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:21:08 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/20 00:44:44 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "vm/bytecode.h"

t_result	parse_group(t_parser *p, t_token token)
{
	t_result	result;
	size_t		pos;

	(void)token;
	program_write_u8(&p->program, OP_SUBSHELL);
	pos = p->program.len;
	program_write_i32(&p->program, 0);
	result = parser_parse_expr(p, PREC_NUL);
	if (result != RESULT_OK)
		return (result);
	result = parser_consume(p, TOK_PAREN_CLOSE, "Expected ')'");
	ft_memcpy(p->program.data + pos, &p->program.len, sizeof(int32_t));
	return (result);
}
