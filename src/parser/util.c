/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:15:20 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 22:53:52 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

void	parser_advance(t_parser *p)
{
	p->prev_token = p->curr_token;
	p->curr_token = lexer_advance(p->lexer);
}

t_result	parser_consume(t_parser *p,
	t_token_type type, const char *error)
{
	if (p->curr_token.type == type)
	{
		parser_advance(p);
		return (RESULT_OK);
	}
	print_error(p, p->curr_token, error);
	return (RESULT_ERROR);
}

bool	parser_match(t_parser *p, t_token_type type)
{
	if (p->curr_token.type == type)
	{
		parser_advance(p);
		return (true);
	}
	return (false);
}
