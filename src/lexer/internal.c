/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:33:36 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/09 23:31:17 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "lexer/lexer_internal.h"

bool	is_operator(char sc)
{
	unsigned char	c;

	c = (unsigned char)sc;
	return (ft_isspace(c) || c == '|' || c == '&'
		|| c == '<' || c == '>' || c == ';'
		|| c == '`' || c == '(' || c == ')'
		|| c == '\0' || c == 0x7fu);
}

char	lexer_next(t_lexer *lexer)
{
	if (lexer->input[lexer->i + 1] == '\0')
		return ('\0');
	lexer->i++;
	lexer->col++;
	lexer->len++;
	if (lexer->input[lexer->i] == '\n')
	{
		lexer->row++;
		lexer->col = 1;
	}
	return (lexer->input[lexer->i]);
}

bool	lexer_match(t_lexer *lexer, char c)
{
	if (lexer->input[lexer->i + 1] == c)
	{
		lexer_next(lexer);
		return (true);
	}
	return (false);
}

t_token	lexer_emit(t_lexer *lexer, t_token_type type)
{
	t_token	tok;

	tok.type = type;
	tok.fd = lexer->fd;
	tok.pos.start = lexer->i - lexer->len + 1;
	tok.pos.col = lexer->col - lexer->len;
	tok.pos.row = lexer->row;
	tok.pos.len = lexer->len;
	return (tok);
}
