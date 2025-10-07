/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:08:36 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/05 20:30:51 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "token.h"

t_parse_rule	parser_get_rule(t_token_type type)
{
	return ((t_parse_rule[TOK_COUNT]){
		[TOK_ERROR] = {PREC_MAX, {0}, parse_error, parse_error},
		[TOK_WORD] = {PREC_LIT, {0}, parse_word, NULL},
		[TOK_PIPE] = {PREC_PIPE, {0}, NULL, parse_pipe},
		[TOK_PAREN_OPEN] = {PREC_NUL, {0}, parse_group, NULL},
		[TOK_EOF] = {PREC_NUL, {0}, NULL, NULL},
		[TOK_AND] = {PREC_LOGIC, {0}, NULL, parse_and},
		[TOK_OR] = {PREC_LOGIC, {0}, NULL, parse_or},
		[TOK_SEMI] = {PREC_LIST, {0}, NULL, parse_semi},
		[TOK_REDIR_OUT] = {PREC_REDIR, {0}, parse_r_out, NULL},
	}[type]);
}
