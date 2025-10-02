/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:08:36 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/13 11:07:18 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parse_rule	parser_get_rule(t_token_type type)
{
	return ((t_parse_rule[TOK_COUNT]){
		[TOK_ERROR] = {PREC_MAX, parse_error, parse_error},
		[TOK_WORD] = {PREC_LIT, parse_command, NULL},
		[TOK_SUB_OPEN] = {PREC_NUL, parse_subcommand, NULL},
		[TOK_PIPE] = {PREC_PIPE, NULL, parse_pipe},
		[TOK_PAREN_OPEN] = {PREC_NUL, parse_group, NULL},
		[TOK_EOF] = {PREC_NUL, NULL, NULL},
		[TOK_AND] = {PREC_LOGIC, NULL, parse_and},
		[TOK_OR] = {PREC_LOGIC, NULL, parse_or},
		[TOK_SEMI] = {PREC_LIST, NULL, parse_semi},
		[TOK_BACKGROUND] = {PREC_LIST, NULL, parse_background},
		[TOK_REDIR_OUT] = {PREC_REDIR, parse_r_out, NULL},
	}[type]);
}
