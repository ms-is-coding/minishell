/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:08:36 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/13 19:44:53 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "parser/parser.h"

/**
 * @brief Parses a comment token.
 *
 * @param p Pointer to the parser structure
 * @param t Comment token to parse
 * @return Always eturns RESULT_OK as comments are ignored.
 */
static t_result	parse_comment(t_parser *p, t_token t)
{
	(void)p;
	(void)t;
	return (RESULT_OK);
}

/**
 * @brief Retrieves the parsing rule for a given token type.
 *
 * @param type Token type
 * @return Corresponding parsing rule.
 */
t_parse_rule	parser_get_rule(t_token_type type)
{
	return ((t_parse_rule[TOK_COUNT]){
		[TOK_COMMENT] = {PREC_MAX, {0}, parse_comment, parse_comment},
		[TOK_ERROR] = {PREC_MAX, {0}, parse_error, parse_error},
		[TOK_WORD] = {PREC_LIT, {0}, parse_word, parse_word},
		[TOK_PIPE] = {PREC_PIPE, {0}, NULL, parse_pipe},
		[TOK_PAREN_OPEN] = {PREC_NUL, {0}, parse_group, NULL},
		[TOK_EOF] = {PREC_NUL, {0}, NULL, NULL},
		[TOK_AND] = {PREC_LOGIC, {0}, NULL, parse_and},
		[TOK_OR] = {PREC_LOGIC, {0}, NULL, parse_or},
		[TOK_SEMI] = {PREC_LIST, {0}, NULL, parse_semi},
		[TOK_REDIR_OUT] = {PREC_REDIR, {0}, parse_r_out, parse_r_out},
		[TOK_REDIR_APPEND] = {PREC_REDIR, {0}, parse_r_out, parse_r_out},
		[TOK_REDIR_IN] = {PREC_REDIR, {0}, parse_r_in, parse_r_in},
		[TOK_REDIR_BOTH] = {PREC_REDIR, {0}, parse_r_in, parse_r_in},
		[TOK_REDIR_HEREDOC] = {PREC_REDIR, {0}, parse_heredoc, parse_heredoc},
	}[type]);
}
