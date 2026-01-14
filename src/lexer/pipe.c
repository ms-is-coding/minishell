/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:34:17 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:38:52 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

/**
 * @brief Lexes pipe-related tokens.
 *
 * @param lexer Pointer to the lexer instance
 * @return The lexed token.
 */
t_token	lex_pip(t_lexer *lexer)
{
	if (lexer_match(lexer, '|'))
		return (lexer_emit(lexer, TOK_OR));
	return (lexer_emit(lexer, TOK_PIPE));
}
