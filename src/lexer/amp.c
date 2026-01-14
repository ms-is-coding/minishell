/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:35:14 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:36:06 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

/**
 * @brief Lexes ampersand-related tokens.
 *
 * @param lexer Pointer to the lexer instance
 * @return The lexed token.
 */
t_token	lex_amp(t_lexer *lexer)
{
	if (lexer_match(lexer, '&'))
	{
		if (lexer_match(lexer, ';'))
			return (lexer_emit(lexer, TOK_DOUBLE_SEMI_AMP));
		return (lexer_emit(lexer, TOK_AND));
	}
	if (lexer_match(lexer, ';'))
		return (lexer_emit(lexer, TOK_SEMI_AMP));
	return (lexer_emit(lexer, TOK_BACKGROUND));
}
