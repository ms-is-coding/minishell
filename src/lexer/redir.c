/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:34:41 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 18:34:54 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_redir_in(t_lexer *lexer)
{
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

t_token	lex_redir_out(t_lexer *lexer)
{
	if (lexer_match(lexer, '>'))
		return (lexer_emit(lexer, TOK_REDIR_APPEND));
	if (lexer_match(lexer, '&'))
		return (lexer_emit(lexer, TOK_REDIR_DUP_OUT));
	return (lexer_emit(lexer, TOK_REDIR_OUT));
}
