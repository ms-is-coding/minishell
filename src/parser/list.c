/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:20:21 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/15 11:59:45 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "vm/bytecode.h"

/**
 * @brief Parses a semicolon token, indicating the end of a command.
 *
 * @param p Pointer to the parser structure
 * @param token Semicolon token to parse
 * @return RESULT_OK on success, otherwise RESULT_ERROR.
 */
t_result	parse_semi(t_parser *p, t_token token)
{
	if (p->curr_token.type == TOK_EOF
		|| p->curr_token.type == TOK_PAREN_CLOSE)
		return (RESULT_OK);
	if ((p->program.data[p->program.len - 1] & OPCODE_MASK) == OP_EXEC)
		p->program.data[p->program.len - 1] |= EXEC_WAIT_BIT;
	else
		program_write_u8(&p->program, OP_EXEC);
	return (parser_parse_expr(p, parser_get_rule(token.type).precedence));
}
