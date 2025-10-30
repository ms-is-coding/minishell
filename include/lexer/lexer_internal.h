/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:49:09 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/30 15:56:11 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include "lexer.h"

bool		is_operator(char c);

char		lexer_next(t_lexer *lexer);
void		lexer_back(t_lexer *lexer);
bool		lexer_match(t_lexer *lexer, char c);
t_token		lexer_emit(t_lexer *lexer, t_token_type type);

typedef t_token	(*t_lex_fn)(t_lexer *lexer);

// Lexing functions

t_token		lex_err(t_lexer *lexer);
t_token		lex_eof(t_lexer *lexer);
t_token		lex_cmt(t_lexer *lexer);
t_token		lex_wrd(t_lexer *lexer);
t_token		lex_nbr(t_lexer *lexer);
t_token		lex_dlm(t_lexer *lexer);
t_token		lex_out(t_lexer *lexer);
t_token		lex_rin(t_lexer *lexer);
t_token		lex_sqt(t_lexer *lexer);
t_token		lex_dqt(t_lexer *lexer);
t_token		lex_grp(t_lexer *lexer);
t_token		lex_amp(t_lexer *lexer);
t_token		lex_pip(t_lexer *lexer);
t_token		lex_dlr(t_lexer *lexer);

#endif // LEXER_INTERNAL_H
