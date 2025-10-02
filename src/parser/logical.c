/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:20:53 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 00:34:19 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bytecode.h"
#include "libft.h"
#include "parser.h"

t_result	parse_and(t_parser *p, t_token token)
{
	size_t		pos;
	t_result	result;

	chunk_write_u8(&p->chunk, OP_JNZ);
	pos = p->chunk.len;
	chunk_write_i32(&p->chunk, 0);
	result = parser_parse_expr(p, parser_get_rule(token.type).precedence);
	ft_memcpy(p->chunk.data + pos, &p->chunk.len, sizeof(int32_t));
	return (result);
}

t_result	parse_or(t_parser *p, t_token token)
{
	size_t		pos;
	t_result	result;

	chunk_write_u8(&p->chunk, OP_JZ);
	pos = p->chunk.len;
	chunk_write_i32(&p->chunk, 0);
	result = parser_parse_expr(p, parser_get_rule(token.type).precedence);
	ft_memcpy(p->chunk.data + pos, &p->chunk.len, sizeof(int32_t));
	return (result);
}
