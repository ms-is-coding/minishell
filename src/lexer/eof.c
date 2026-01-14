/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:48:30 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:37:24 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

/**
 * @brief Lexes the end-of-file token.
 *
 * @param lexer Pointer to the lexer instance
 * @return The lexed token.
 */
t_token	lex_eof(t_lexer *lexer)
{
	return (lexer_emit(lexer, TOK_EOF));
}
