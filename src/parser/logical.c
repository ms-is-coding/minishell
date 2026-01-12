/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:20:53 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 17:01:40 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"
#include "parser/parser.h"

t_result	parse_and(t_parser *p, t_token token)
{
	size_t		pos;
	t_result	result;

	if (p->program.data[p->program.len - 1] == OP_EXEC)
		p->program.data[p->program.len - 1] |= EXEC_WAIT_BIT;
	program_write_u8(&p->program, OP_JUMP | JUMP_NEG_BIT);
	pos = p->program.len;
	program_write_i32(&p->program, 0);
	result = parser_parse_expr(p, parser_get_rule(token.type).precedence);
	ft_memcpy(p->program.data + pos, &p->program.len, sizeof(int32_t));
	return (result);
}

t_result	parse_or(t_parser *p, t_token token)
{
	size_t		pos;
	t_result	result;

	if (p->program.data[p->program.len - 1] == OP_EXEC)
		p->program.data[p->program.len - 1] |= EXEC_WAIT_BIT;
	program_write_u8(&p->program, OP_JUMP);
	pos = p->program.len;
	program_write_i32(&p->program, 0);
	result = parser_parse_expr(p, parser_get_rule(token.type).precedence);
	ft_memcpy(p->program.data + pos, &p->program.len, sizeof(int32_t));
	return (result);
}
