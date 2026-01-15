/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:15:20 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/15 12:22:58 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

/**
 * @brief Advances the parser to the next token.
 *
 * @param p Pointer to the parser structure
 */
void	parser_advance(t_parser *p)
{
	p->prev_token = p->curr_token;
	p->curr_token = lexer_advance(p->lexer);
}

/**
 * @brief Consumes a token of the expected type.
 *
 * @param p Pointer to the parser structure
 * @param type Expected token type
 * @param error Error message to display if the token type does not match
 * @return RESULT_OK if the token type matches, otherwise RESULT_ERROR.
 */
t_result	parser_consume(t_parser *p,
	t_token_type type, const char *error)
{
	if (p->curr_token.type == type)
	{
		parser_advance(p);
		return (RESULT_OK);
	}
	if (p->curr_token.type == TOK_EOF)
		print_error(p, p->prev_token, error);
	else
		print_error(p, p->curr_token, error);
	return (RESULT_ERROR);
}

/**
 * @brief Checks if the current token matches the expected type and advances
 * the parser.
 *
 * @param p Pointer to the parser structure
 * @param type Expected token type
 * @return true if the token type matches and the parser advanced, false
 * otherwise.
 */
bool	parser_match(t_parser *p, t_token_type type)
{
	if (p->curr_token.type == type)
	{
		parser_advance(p);
		return (true);
	}
	return (false);
}
