/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:02:49 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:38:39 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"
#include <limits.h>
#include <stdbool.h>

/**
 * @brief Loops through double-quoted strings.
 *
 * @param lexer Pointer to the lexer instance
 * @return RESULT_OK on success, RESULT_ERROR on failure.
 */
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

/**
 * @brief Loops through single-quoted strings.
 *
 * @param lexer Pointer to the lexer instance
 * @return RESULT_OK on success, RESULT_ERROR on failure.
 */
static t_result	squote_loop(t_lexer *lexer)
{
	while (lexer->next_char && lexer->next_char != '\'')
		lexer_next(lexer);
	if (lexer->next_char != '\'')
		return (RESULT_ERROR);
	lexer_next(lexer);
	return (RESULT_OK);
}

/**
 * @brief Lexes word tokens.
 *
 * @param lexer Pointer to the lexer instance
 * @return The lexed token.
 */
t_token	lex_wrd(t_lexer *lexer)
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
