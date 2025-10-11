/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:13:49 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/09 23:58:27 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "parser/parser.h"
#include "ansi.h"
#include "vm/bytecode.h"

static void	repeat(char c, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		ft_dprintf(2, "%c", c);
}

static void	print_line(t_parser *p, t_token token)
{
	if (token.pos.len > ERROR_MAX_LENGTH)
	{
		ft_dprintf(2, ANSI_RED "%.*s...%.*s" ANSI_RESET,
			ERROR_CHARACTERS, p->lexer->input + token.pos.col - 1,
			ERROR_CHARACTERS, p->lexer->input + token.pos.col - 1
			+ token.pos.len - ERROR_CHARACTERS);
	}
	else
		ft_dprintf(2, ANSI_RED "%.*s" ANSI_RESET, token.pos.len,
			p->lexer->input + token.pos.col - 1);
}

void	print_error(t_parser *p, t_token token, const char *message)
{
	repeat(' ', ft_intlen(token.pos.row) + 2);
	ft_dprintf(2, "┌─ " ANSI_BLUE "REPL" ANSI_RESET ":" ANSI_YELLOW "%d"
		ANSI_RESET ":" ANSI_YELLOW "%d" ANSI_RESET, token.pos.row,
		token.pos.col);
	ft_dprintf(2, ANSI_BOLD ANSI_RED " Syntax Error\n" ANSI_RESET);
	ft_dprintf(2, " " ANSI_BOLD "%d │ " ANSI_RESET, token.pos.row);
	if (token.pos.col - 1 > ERROR_CHARACTERS + 3)
		ft_dprintf(2, "...%.*s", ERROR_CHARACTERS,
			p->lexer->input + token.pos.col - 1 - ERROR_CHARACTERS);
	else
		ft_dprintf(2, "%.*s", token.pos.col - 1, p->lexer->input);
	print_line(p, token);
	if (ft_strlen(p->lexer->input + token.pos.col - 1 + token.pos.len)
		> ERROR_CHARACTERS + 3)
		ft_dprintf(2, "%.*s...\n", ERROR_CHARACTERS,
			p->lexer->input + token.pos.col - 1 + token.pos.len);
	else
		ft_dprintf(2, "%s\n", p->lexer->input + token.pos.col - 1
			+ token.pos.len);
	repeat(' ', ft_intlen(token.pos.row) + 2);
	ft_dprintf(2, "╵");
	if (token.pos.col - 1 > ERROR_CHARACTERS + 3)
		repeat(' ', ERROR_CHARACTERS + 4);
	else
		repeat(' ', token.pos.col);
	ft_dprintf(2, ANSI_RED "^");
	if (token.pos.len > ERROR_MAX_LENGTH)
		repeat('~', ERROR_MAX_LENGTH - 1);
	else
		repeat('~', token.pos.len - 1);
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
		print_error(p, token, "Unexpected token");
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
			print_error(p, oper_token, "Unexpected operator");
			return (RESULT_ERROR);
		}
		parser_advance(p);
		if (rule.led(p, oper_token) != RESULT_OK)
			return (RESULT_ERROR);
	}
	if (p->program.data[p->program.len - 1] == OP_EXEC)
		p->program.data[p->program.len - 1] |= EXEC_WAIT_BIT;
	return (RESULT_OK);
}
