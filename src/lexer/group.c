/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:36:17 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:37:37 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

#define UNREACHABLE TOK_ERROR

/**
 * @brief Lexes group-related tokens.
 *
 * @param lexer Pointer to the lexer instance
 * @return The lexed token.
 */
t_token	lex_grp(t_lexer *lexer)
{
	if (lexer->curr_char == '(')
		return (lexer_emit(lexer, TOK_PAREN_OPEN));
	if (lexer->curr_char == ')')
		return (lexer_emit(lexer, TOK_PAREN_CLOSE));
	return (lexer_emit(lexer, UNREACHABLE));
}
