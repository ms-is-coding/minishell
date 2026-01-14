/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:33:05 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:37:31 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

/**
 * @brief Lexes the end-of-file token.
 *
 * @param lexer Pointer to the lexer instance
 * @return The lexed token.
 */
t_token	lex_err(t_lexer *lexer)
{
	return (lexer_emit(lexer, TOK_ERROR));
}
