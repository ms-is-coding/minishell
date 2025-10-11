/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:08:36 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/11 18:56:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/parser.h"

static t_result	parse_comment(t_parser *p, t_token t)
{
	(void)p;
	(void)t;
	return (RESULT_OK);
}

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
	}[type]);
}
