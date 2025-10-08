/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:36:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 14:21:45 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

#define UNREACHABLE TOK_ERROR

t_token	lex_group(t_lexer *lexer)
{
	if (lexer->input[lexer->i] == '(')
		return (lexer_emit(lexer, TOK_PAREN_OPEN));
	if (lexer->input[lexer->i] == ')')
		return (lexer_emit(lexer, TOK_PAREN_CLOSE));
	return (lexer_emit(lexer, UNREACHABLE));
}
