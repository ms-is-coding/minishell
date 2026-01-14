/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:33:36 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/13 19:40:28 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/ctype.h"
#include "lexer/lexer.h"
#include "lexer/lexer_internal.h"

/**
 * @brief Checks if the given character is an operator.
 *
 * @param sc Character to check
 * @return true if the character is an operator, false otherwise.
 */
bool	is_operator(char sc)
{
	unsigned char	c;

	c = (unsigned char)sc;
	return (ft_isspace(c) || c == '|' || c == '&'
		|| c == '<' || c == '>' || c == ';'
		|| c == '`' || c == '(' || c == ')'
		|| c == '\0' || c == 0x7fu);
}

/**
 * @brief Advances the lexer to the next character, updating its state accordingly.
 *
 * @param lexer Pointer to the lexer structure
 * @return The next character.
 */
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

/**
 * @brief Moves the lexer back by one character, updating its state accordingly.
 *
 * @param lexer Pointer to the lexer structure
 */
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

/**
 * @brief Matches the next character in the lexer with the given character.
 *
 * @param lexer Pointer to the lexer structure
 * @param c Character to match
 * @return true if the characters match, false otherwise.
 */
bool	lexer_match(t_lexer *lexer, char c)
{
	if (lexer->next_char == c)
	{
		lexer_next(lexer);
		return (true);
	}
	return (false);
}

/**
 * @brief Emits a token of the given type from the lexer.
 *
 * @param lexer Pointer to the lexer structure
 * @param type Type of the token to emit
 * @return The emitted token.
 */
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
