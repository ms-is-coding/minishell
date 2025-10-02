/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:13:49 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 17:01:28 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "ansi.h"

static void	repeat(char *s, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		ft_dprintf(2, "%s", s);
}

static void	print_error(t_parser *p, t_token token, char *message)
{
	repeat(" ", ft_intlen(token.pos.row) + 2);
	ft_dprintf(2, "┌─ " ANSI_BLUE "REPL" ANSI_RESET ":" ANSI_YELLOW "%d"
		ANSI_RESET ":" ANSI_YELLOW "%d" ANSI_RESET, token.pos.row,
		token.pos.col);
	ft_dprintf(2, ANSI_BOLD ANSI_RED " Syntax Error\n" ANSI_RESET);
	ft_dprintf(2, " " ANSI_BOLD "%d │ " ANSI_RESET, token.pos.row);
	ft_dprintf(2, "%.*s", token.pos.col - 1, p->lexer->input);
	ft_dprintf(2, ANSI_RED "%.*s" ANSI_RESET, token.pos.len,
		p->lexer->input + token.pos.col - 1);
	ft_dprintf(2, "%s\n", p->lexer->input + token.pos.col - 1 + token.pos.len);
	repeat(" ", ft_intlen(token.pos.row) + 2);
	ft_dprintf(2, "╵");
	repeat(" ", token.pos.col);
	ft_dprintf(2, ANSI_RED "^");
	repeat("~", token.pos.len - 1);
	ft_dprintf(2, ANSI_RED " %s\n\n" ANSI_RESET, message);
}

t_result	parser_parse_expr(t_parser *p, t_precedence prec)
{
	t_token			token;
	t_token			oper_token;
	t_parse_rule	rule;
	bool			same_line;

	(void)same_line;
	token = p->curr_token;
	parser_advance(p);
	rule = parser_get_rule(token.type);
	if (!rule.nud)
	{
		print_error(p, token, "unexpected token");
		return (RESULT_ERROR);
	}
	if (rule.nud(p, token) != RESULT_OK)
		return (RESULT_ERROR);
	while (prec < parser_get_rule(p->curr_token.type).precedence)
	{
		oper_token = p->curr_token;
		if (oper_token.type == TOK_EOF)
			break ;
		same_line = token.pos.row == oper_token.pos.row;
		rule = parser_get_rule(oper_token.type);
		if (!rule.led)
		{
			print_error(p, token, "unexpected operator");
			return (RESULT_ERROR);
		}
		parser_advance(p);
		if (rule.led(p, oper_token) != RESULT_OK)
			return (RESULT_ERROR);
	}
	return (RESULT_OK);
}
