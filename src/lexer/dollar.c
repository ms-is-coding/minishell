/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:35:44 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:37:19 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

/**
 * @brief Lexes dollar-related tokens.
 *
 * @param lexer Pointer to the lexer instance
 * @return The lexed token.
 */
t_token	lex_dlr(t_lexer *lexer)
{
	if (lexer_match(lexer, '('))
	{
		if (lexer_match(lexer, '('))
			return (lexer_emit(lexer, TOK_MATH_OPEN));
		return (lexer_emit(lexer, TOK_SUB_OPEN));
	}
	return (lex_wrd(lexer));
}
