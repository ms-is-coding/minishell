/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:26:53 by smamalig          #+#    #+#             */
/*   Updated: 2025/08/25 08:01:45 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_result	parser_init(t_parser *p, t_lexer *lexer)
{
	p->lexer = lexer;
	p->curr_token = (t_token){0};
	p->prev_token = (t_token){0};
	p->chunk.len = 0;
	p->in_cmd = false;
	return (RESULT_OK);
}
