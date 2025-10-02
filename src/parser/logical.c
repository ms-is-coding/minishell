/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:20:53 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 17:02:08 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/parser.h"

t_result	parse_and(t_parser *p, t_token token)
{
	size_t		pos;
	t_result	result;

	program_write_u8(&p->program, OP_JNZ);
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

	program_write_u8(&p->program, OP_JZ);
	pos = p->program.len;
	program_write_i32(&p->program, 0);
	result = parser_parse_expr(p, parser_get_rule(token.type).precedence);
	ft_memcpy(p->program.data + pos, &p->program.len, sizeof(int32_t));
	return (result);
}
