/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:37:50 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/17 00:39:29 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander_internal.h"

bool	dquote_escape(char c)
{
	return (c == '$' || c == '\\' || c == '"');
}

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

bool	is_var_operator(char sc)
{
	unsigned char	c;

	c = (unsigned char)sc;
	return (ft_isspace(c) || c == '|' || c == '&'
		|| c == '<' || c == '>' || c == ';'
		|| c == '`' || c == '(' || c == ')'
		|| c == '$' || c == '[' || c == ']'
		|| c == '"' || c == '\''
		|| c == '\0' || c == 0x7fu);
}
