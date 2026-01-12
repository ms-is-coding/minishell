/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:33:36 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 16:53:59 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/ctype.h"
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
	if (lexer->end)
		return ('\0');
	lexer->curr_char = lexer->next_char;
	if (lexer->curr_char == '\0')
	{
		lexer->end = true;
		return ('\0');
	}
	lexer->col++;
	lexer->len++;
	if (lexer->curr_char == '\n')
	{
		lexer->row++;
		lexer->col = 1;
	}
	lexer->next_char = lexer->input[++lexer->i];
	return (lexer->curr_char);
}

void	lexer_back(t_lexer *lexer)
{
	lexer->next_char = lexer->curr_char;
	lexer->len--;
	lexer->col--;
	if (lexer->i == 0)
		lexer->curr_char = '\0';
	else
		lexer->curr_char = lexer->input[--lexer->i];
}

bool	lexer_match(t_lexer *lexer, char c)
{
	if (lexer->next_char == c)
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
	tok.pos.start = lexer->i - lexer->len;
	tok.pos.col = lexer->col - lexer->len;
	tok.pos.row = lexer->row;
	tok.pos.len = lexer->len;
	return (tok);
}
