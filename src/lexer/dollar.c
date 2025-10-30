/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:35:44 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/30 16:43:53 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_dlr(t_lexer *lexer)
{
	if (lexer_match(lexer, '('))
	{
		if (lexer_match(lexer, '('))
			return (lexer_emit(lexer, TOK_MATH_OPEN));
		return (lexer_emit(lexer, TOK_SUB_OPEN));
	}
	return (lex_wrd(lexer));
}
