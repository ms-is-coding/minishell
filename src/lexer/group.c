/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:36:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/11 12:26:22 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

#define UNREACHABLE TOK_ERROR

t_token	lex_group(t_lexer *lexer)
{
	if (lexer->curr_char == '(')
		return (lexer_emit(lexer, TOK_PAREN_OPEN));
	if (lexer->curr_char == ')')
		return (lexer_emit(lexer, TOK_PAREN_CLOSE));
	return (lexer_emit(lexer, UNREACHABLE));
}
