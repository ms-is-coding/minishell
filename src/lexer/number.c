/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:49:18 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:38:45 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

/**
 * @brief Lexes number tokens, handling redirection operators.
 *
 * @param lexer Pointer to the lexer instance
 * @return The lexed token.
 */
t_token	lex_nbr(t_lexer *lexer)
{
	lexer->fd = lexer->curr_char - '0';
	while (lexer->next_char >= '0'
		&& lexer->next_char <= '9')
	{
		if (lexer->fd > INT_MAX / 10 || (
				lexer->fd == INT_MAX / 10 && lexer->next_char > '7'))
		{
			lexer->fd = -1;
			return (lex_wrd(lexer));
		}
		lexer->fd = lexer->fd * 10 + (lexer_next(lexer) - '0');
	}
	if (lexer_match(lexer, '>'))
		return (lex_out(lexer));
	if (lexer_match(lexer, '<'))
		return (lex_rin(lexer));
	return (lex_wrd(lexer));
}
