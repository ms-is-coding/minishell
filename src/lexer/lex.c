/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:02:49 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/17 15:28:07 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"
#include <limits.h>
#include <stdbool.h>

static t_result	dquote_loop(t_lexer *lexer)
{
	while (lexer->next_char && lexer->next_char != '"')
	{
		if (lexer->next_char == '\\')
			lexer_next(lexer);
		lexer_next(lexer);
	}
	if (lexer->next_char != '"')
		return (RESULT_ERROR);
	lexer_next(lexer);
	return (RESULT_OK);
}

static t_result	squote_loop(t_lexer *lexer)
{
	while (lexer->next_char && lexer->next_char != '\'')
		lexer_next(lexer);
	if (lexer->next_char != '\'')
		return (RESULT_ERROR);
	lexer_next(lexer);
	return (RESULT_OK);
}

t_token	lex_word(t_lexer *lexer)
{
	lexer_back(lexer);
	while (lexer->next_char && !is_operator(lexer->next_char))
	{
		lexer_next(lexer);
		if (lexer->curr_char == '\\')
		{
			if (lexer->next_char == '\0')
				return (lexer_emit(lexer, TOK_ERROR));
			lexer_next(lexer);
			continue ;
		}
		if (lexer->curr_char == '"'
			&& dquote_loop(lexer) != RESULT_OK)
			return (lexer_emit(lexer, TOK_ERROR));
		if (lexer->curr_char == '\''
			&& squote_loop(lexer) != RESULT_OK)
			return (lexer_emit(lexer, TOK_ERROR));
	}
	return (lexer_emit(lexer, TOK_WORD));
}
