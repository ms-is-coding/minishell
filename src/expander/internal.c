/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:37:50 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/15 11:56:20 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander_internal.h"
#include "core/ctype.h"

/**
 * @brief Checks if a character should be escaped in double quotes.
 * @param c The character to check
 * @return true if the character should be escaped, false otherwise.
 */
bool	dquote_escape(char c)
{
	return (c == '$' || c == '\\' || c == '"');
}

/**
 * @brief Retrieves the next character from the expander.
 * @param exp Pointer to the expander
 * @return The next character, or '\0' if the end is reached.
 */
char	expander_next(t_expander *exp)
{
	char	ret;

	if (exp->end)
		return ('\0');
	ret = exp->next_char;
	if (exp->i < exp->arg_len)
		exp->next_char = exp->arg[exp->i++];
	else
	{
		exp->next_char = '\0';
		exp->end = true;
	}
	exp->curr_char = ret;
	return (ret);
}

/**
 * @brief Checks if a character is a variable operator.
 *
 * @param sc The character to check
 * @return true if the character is a variable operator, false otherwise.
 */
bool	is_var_operator(char sc)
{
	unsigned char	c;

	c = (unsigned char)sc;
	return (ft_isspace(c) || c == '|' || c == '&'
		|| c == '<' || c == '>' || c == ';'
		|| c == '`' || c == '(' || c == ')'
		|| c == '$' || c == '[' || c == ']'
		|| c == '"' || c == '\'' || c == '/'
		|| c == '=' || c == '\0' || c == 0x7fu);
}
