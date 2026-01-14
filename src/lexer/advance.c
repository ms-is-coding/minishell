/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:30:58 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/13 19:36:24 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

#define LEX_NIL NULL

static t_lex_fn	g_lex_fns[128] = {
	lex_eof, lex_err, lex_err, lex_err, lex_err, lex_err, lex_err, lex_err,
	lex_err, LEX_NIL, LEX_NIL, lex_err, lex_err, lex_err, lex_err, lex_err,
	lex_err, lex_err, lex_err, lex_err, lex_err, lex_err, lex_err, lex_err,
	lex_err, lex_err, lex_err, lex_err, lex_err, lex_err, lex_err, lex_err,
	LEX_NIL, lex_err, lex_wrd, lex_cmt, lex_dlr, lex_err, lex_amp, lex_wrd,
	lex_grp, lex_grp, lex_wrd, lex_wrd, lex_err, lex_wrd, lex_wrd, lex_wrd,
	lex_nbr, lex_nbr, lex_nbr, lex_nbr, lex_nbr, lex_nbr, lex_nbr, lex_nbr,
	lex_nbr, lex_nbr, lex_wrd, lex_dlm, lex_rin, lex_wrd, lex_out, lex_wrd,
	lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd,
	lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd,
	lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd,
	lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd,
	lex_err, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd,
	lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd,
	lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd, lex_wrd,
	lex_wrd, lex_wrd, lex_wrd, lex_err, lex_pip, lex_err, lex_wrd, lex_err
};

/**
 * @brief Advances the lexer to the next token.
 *
 * @param lexer Pointer to the lexer structure
 * @return The next token.
 */
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
		fn = g_lex_fns[(int)c];
		if (fn)
			return (fn(lexer));
	}
}
