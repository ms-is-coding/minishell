/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:03:47 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/15 11:59:51 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "parser/parser.h"
#include "vm/bytecode.h"

/**
 * @brief Handles parse errors for unterminated strings & prints a message.
 *
 * @param p Pointer to the parser structure
 * @param token Token that caused the parse error
 * @return Result indicating a parse error.
 */
t_result	parse_error(t_parser *p, t_token token)
{
	print_error(p, token, "Unterminated string");
	return (RESULT_ERROR);
}

/**
 * @brief Parses a pipeline expression.
 *
 * @param p Pointer to the parser structure
 * @param token Pipeline token to parse
 * @return Result of the parsing operation.
 */
t_result	parse_pipe(t_parser *p, t_token token)
{
	if (p->mode == PARSER_MODE_GROUP)
	{
		print_error(p, token, "Pipes cannot be used when parentheses are"\
			" present");
		return (RESULT_ERROR);
	}
	p->mode = PARSER_MODE_PIPE;
	if ((p->program.data[p->program.len - 1] & OPCODE_MASK) == OP_EXEC)
		p->program.data[p->program.len - 1] = OP_EXEC | EXEC_PIPELINE_BIT;
	else
		program_write_u8(&p->program, OP_EXEC | EXEC_PIPELINE_BIT);
	return (parser_parse_expr(p, parser_get_rule(token.type).precedence));
}

/**
 * @brief Parses the input line and constructs the program bytecode.
 *
 * @param p Pointer to the parser structure
 * @param line Input line to parse
 * @return Result of the parsing operation.
 */
t_result	parser_parse(t_parser *p, char *line)
{
	t_result	result;

	lexer_init(p->lexer, line);
	parser_init(p, p->lexer);
	parser_advance(p);
	while (p->curr_token.type != TOK_EOF)
	{
		result = parser_parse_expr(p, PREC_NUL);
		if (result != RESULT_OK)
			return (result);
	}
	return (RESULT_OK);
}
