/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:32:43 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:37:13 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

/**
 * @brief Lexes delimiter-related tokens.
 *
 * @param lexer Pointer to the lexer instance
 * @return The lexed token.
 */
t_token	lex_dlm(t_lexer *lexer)
{
	if (lexer_match(lexer, ';'))
		return (lexer_emit(lexer, TOK_DOUBLE_SEMI));
	return (lexer_emit(lexer, TOK_SEMI));
}
