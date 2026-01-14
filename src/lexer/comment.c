/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:47:34 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:36:31 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

/**
 * @brief Lexes a comment token.
 *
 * @param lexer Pointer to the lexer instance
 * @return The lexed comment token.
 */
t_token	lex_cmt(t_lexer *lexer)
{
	while (lexer->next_char != '\n'
		&& lexer->next_char != '\0')
		lexer_next(lexer);
	return (lexer_emit(lexer, TOK_COMMENT));
}
