/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:02:49 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/09 22:53:17 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"
#include "token.h"
#include <limits.h>
#include <stdbool.h>

static t_result	dquote_loop(t_lexer *lexer)
{
	while (lexer->input[lexer->i + 1] && lexer->input[lexer->i + 1] != '"')
	{
		if (lexer->input[lexer->i + 1] == '\\')
			lexer_next(lexer);
		lexer_next(lexer);
	}
	if (lexer->input[lexer->i + 1] != '"')
		return (RESULT_ERROR);
	lexer_next(lexer);
	return (RESULT_OK);
}

static t_result	squote_loop(t_lexer *lexer)
{
	while (lexer->input[lexer->i + 1] && lexer->input[lexer->i + 1] != '\'')
		lexer_next(lexer);
	if (lexer->input[lexer->i + 1] != '\'')
		return (RESULT_ERROR);
	lexer_next(lexer);
	return (RESULT_OK);
}

t_token	lex_word(t_lexer *lexer)
{
	while (true)
	{
		if (lexer->input[lexer->i] == '\\')
		{
			if (lexer_next(lexer) == '\0')
				return (lexer_emit(lexer, TOK_ERROR));
			lexer_next(lexer);
			continue ;
		}
		if (lexer->input[lexer->i] == '"'
			&& dquote_loop(lexer) != RESULT_OK)
			return (lexer_emit(lexer, TOK_ERROR));
		if (lexer->input[lexer->i] == '\''
			&& squote_loop(lexer) != RESULT_OK)
			return (lexer_emit(lexer, TOK_ERROR));
		if (is_operator(lexer->input[lexer->i + 1])
			|| lexer->input[lexer->i + 1] == '\0')
			break ;
		lexer_next(lexer);
	}
	return (lexer_emit(lexer, TOK_WORD));
}
