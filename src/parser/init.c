/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:26:53 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/15 11:59:34 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

/**
 * @brief Initializes the parser with the given lexer.
 *
 * @param p Pointer to the parser structure
 * @param lexer Pointer to the lexer structure
 * @return Result of the initialization operation.
 */
t_result	parser_init(t_parser *p, t_lexer *lexer)
{
	p->lexer = lexer;
	p->curr_token = (t_token){0};
	p->prev_token = (t_token){0};
	p->program.len = 0;
	p->in_cmd = false;
	p->mode = PARSER_MODE_NONE;
	return (RESULT_OK);
}
