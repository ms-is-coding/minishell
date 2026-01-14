/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:34:41 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:39:21 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

/**
 * @brief Lexes input redirection tokens.
 *
 * @param lexer Pointer to the lexer instance
 * @return The lexed token.
 */
t_token	lex_rin(t_lexer *lexer)
{
	if (lexer_match(lexer, '>'))
		return (lexer_emit(lexer, TOK_REDIR_BOTH));
	if (lexer_match(lexer, '<'))
	{
		if (lexer_match(lexer, '<'))
			return (lexer_emit(lexer, TOK_REDIR_HERESTRING));
		return (lexer_emit(lexer, TOK_REDIR_HEREDOC));
	}
	if (lexer_match(lexer, '&'))
		return (lexer_emit(lexer, TOK_REDIR_DUP_IN));
	return (lexer_emit(lexer, TOK_REDIR_IN));
}

/**
 * @brief Lexes output redirection tokens.
 *
 * @param lexer Pointer to the lexer instance
 * @return The lexed token.
 */
t_token	lex_out(t_lexer *lexer)
{
	if (lexer_match(lexer, '>'))
		return (lexer_emit(lexer, TOK_REDIR_APPEND));
	if (lexer_match(lexer, '&'))
		return (lexer_emit(lexer, TOK_REDIR_DUP_OUT));
	return (lexer_emit(lexer, TOK_REDIR_OUT));
}
