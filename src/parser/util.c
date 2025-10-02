/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:15:20 by smamalig          #+#    #+#             */
/*   Updated: 2025/08/22 18:17:48 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser_advance(t_parser *p)
{
	p->prev_token = p->curr_token;
	p->curr_token = lexer_advance(p->lexer);
}

t_token	parser_consume(t_parser *p,
	t_token_type type, const char *error)
{
	if (p->curr_token.type == type)
	{
		parser_advance(p);
		return (p->prev_token);
	}
	ft_printf("\x1b[91m[ERR]\x1b[m %s\n", error);
	return (p->curr_token);
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
