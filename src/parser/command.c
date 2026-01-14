/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:10:56 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/13 19:55:28 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "core/string.h"
#include <stddef.h>

/**
 * @brief Parses a command starting with a word token.
 *
 * @param p Pointer to the parser structure
 * @param t Initial word token of the command
 * @return RESULT_OK on success, RESULT_ERROR on failure.
 */
static t_result	parse_command(t_parser *p, t_token t)
{
	size_t	pos;

	p->argc = 0;
	p->redirs = 0;
	program_write_u8(&p->program, OP_CMD);
	pos = p->program.len;
	program_write_i32(&p->program, 0);
	p->in_cmd = true;
	if (parse_word(p, t) != RESULT_OK)
		return (RESULT_ERROR);
	while (p->curr_token.type == TOK_WORD
		|| p->curr_token.type == TOK_REDIR_OUT
		|| p->curr_token.type == TOK_REDIR_APPEND
		|| p->curr_token.type == TOK_REDIR_HEREDOC
		|| p->curr_token.type == TOK_REDIR_IN)
		if (parser_parse_expr(p, PREC_REDIR) != RESULT_OK)
			return (RESULT_ERROR);
	program_write_u8(&p->program, OP_EXEC);
	ft_memcpy(p->program.data + pos, &p->argc, sizeof(int32_t));
	p->in_cmd = false;
	return (RESULT_OK);
}

/**
 * @brief Parses a word token, either as part of a command or as an argument.
 *
 * @param p Pointer to the parser structure
 * @param token Word token to parse
 * @return RESULT_OK on success, RESULT_ERROR on failure.
 */
t_result	parse_word(t_parser *p, t_token token)
{
	if (!p->in_cmd)
		return (parse_command(p, token));
	if (token.pos.len > 0xffff)
	{
		print_error(p, token, "Command too long");
		return (RESULT_ERROR);
	}
	program_write_u8(&p->program, OP_ARG);
	program_write_u16(&p->program, (uint16_t)token.pos.len);
	program_write_str(&p->program, p->lexer->input + token.pos.start,
		(size_t)token.pos.len);
	p->argc++;
	return (RESULT_OK);
}
