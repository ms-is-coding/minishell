/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:13:49 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/15 11:58:58 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "parser/parser.h"
#include "ansi.h"
#include "vm/bytecode.h"
#include "core/stdio.h"
#include "core/math.h"
#include "core/string.h"

/**
 * @brief Prints the line of code where the error occurred.
 *
 * @param p Pointer to the parser structure
 * @param token The token where the error occurred
 */
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

void	print_error(t_parser *p, t_token token, const char *message) //FIX function too long
{
	ft_dprintf(2, "%*s┌─ " ANSI_CYAN "REPL" ANSI_RESET ":" ANSI_YELLOW "%d"
		ANSI_RESET ":" ANSI_YELLOW "%d" ANSI_RESET ANSI_BOLD ANSI_RED
		" Syntax Error" ANSI_RESET "\n " ANSI_BOLD "%d" ANSI_RESET " │ ",
		ft_intlen(token.pos.row) + 2, "", token.pos.row, token.pos.col,
		token.pos.row);
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
	ft_dprintf(2, "%*s╵", ft_intlen(token.pos.row) + 2, "");
	if (token.pos.col - 1 > ERROR_CHARACTERS + 3)
		ft_dprintf(2, "%*s", ERROR_CHARACTERS + 4, "");
	else
		ft_dprintf(2, ANSI_RED "%*s", token.pos.col, "");
	if (token.pos.len > ERROR_MAX_LENGTH)
		ft_dprintf(2, ANSI_RED "%.*s", ERROR_MAX_LENGTH, ERROR_HIGHLIGHT);
	else
		ft_dprintf(2, ANSI_RED "%.*s", token.pos.len, ERROR_HIGHLIGHT);
	ft_dprintf(2, " %s" ANSI_RESET "\n", message);
}

t_result	parser_parse_expr(t_parser *p, t_precedence prec) //function too long
{
	t_token			token;
	t_token			oper_token;
	t_parse_rule	rule;

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
