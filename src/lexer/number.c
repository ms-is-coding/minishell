/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:49:18 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/11 12:25:41 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_number(t_lexer *lexer)
{
	lexer->fd = lexer->curr_char - '0';
	while (lexer->next_char >= '0'
		&& lexer->next_char <= '9')
	{
		if (lexer->fd > INT_MAX / 10 || (
				lexer->fd == INT_MAX / 10 && lexer->next_char > '7'))
		{
			lexer->fd = -1;
			return (lex_word(lexer));
		}
		lexer->fd = lexer->fd * 10 + (lexer_next(lexer) - '0');
	}
	if (lexer_match(lexer, '>'))
		return (lex_redir_out(lexer));
	if (lexer_match(lexer, '<'))
		return (lex_redir_in(lexer));
	return (lex_word(lexer));
}
