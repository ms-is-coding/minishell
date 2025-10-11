/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:30:58 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/11 12:24:51 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

static t_lex_fn	get_fn(int idx)
{
	return ((t_lex_fn[128]){lex_eof, lex_error, lex_error, lex_error, lex_error,
		lex_error, lex_error, lex_error, lex_error, NULL, lex_error, lex_error,
		lex_error, lex_error, lex_error, lex_error, lex_error, lex_error,
		lex_error, lex_error, lex_error, lex_error, lex_error, lex_error,
		lex_error, lex_error, lex_error, lex_error, lex_error, lex_error,
		lex_error, lex_error, NULL, lex_error, lex_word, lex_comment,
		lex_dollar, lex_error, lex_amp, lex_word, lex_group, lex_group,
		lex_word, lex_word, lex_error, lex_word, lex_word, lex_word, lex_number,
		lex_number, lex_number, lex_number, lex_number, lex_number, lex_number,
		lex_number, lex_number, lex_number, lex_word, lex_delim, lex_redir_in,
		lex_word, lex_redir_out, lex_word, lex_word, lex_word, lex_word,
		lex_word, lex_word, lex_word, lex_word, lex_word, lex_word, lex_word,
		lex_word, lex_word, lex_word, lex_word, lex_word, lex_word, lex_word,
		lex_word, lex_word, lex_word, lex_word, lex_word, lex_word, lex_word,
		lex_word, lex_word, lex_word, lex_word, lex_word, lex_word,
		lex_word, lex_word, lex_error, lex_word, lex_word, lex_word, lex_word,
		lex_word, lex_word, lex_word, lex_word, lex_word, lex_word,
		lex_word, lex_word, lex_word, lex_word, lex_word, lex_word, lex_word,
		lex_word, lex_word, lex_word, lex_word, lex_word, lex_word,
		lex_word, lex_word, lex_word, lex_error, lex_pipe, lex_error,
		lex_word, lex_error}[idx]);
}

t_token	lexer_advance(t_lexer *lexer)
{
	char		c;
	t_lex_fn	fn;

	lexer->len = 0;
	lexer->fd = -1;
	if (lexer->end)
		return (lexer_emit(lexer, TOK_EOF));
	while (true)
	{
		lexer->len = 0;
		c = lexer_next(lexer);
		if ((unsigned char)c > (unsigned char)0x7f)
			return (lexer_emit(lexer, TOK_ERROR));
		fn = get_fn(c);
		if (fn)
			return (fn(lexer));
	}
}
