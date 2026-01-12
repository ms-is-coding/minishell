/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:45:44 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 17:34:21 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander_internal.h"
#include "core/string.h"

void	expander_dquote_no_var(t_expander *exp, t_var_expansion_mode mode)
{
	while (exp->next_char && exp->next_char != '"')
	{
		expander_next(exp);
		if (exp->curr_char == '\\' && dquote_escape(exp->next_char))
			expander_next(exp);
		if (mode == VEXPM_EXTRACT)
			ft_strncat(exp->frame->argv[exp->frame->argc], &exp->curr_char, 1);
		exp->len++;
	}
	expander_next(exp);
}

void	expander_dquote(t_expander *exp, t_var_expansion_mode mode)
{
	while (exp->next_char && exp->next_char != '"')
	{
		expander_next(exp);
		if (exp->curr_char == '$')
			expander_var_no_ifs(exp, mode);
		else
		{
			if (exp->curr_char == '\\' && dquote_escape(exp->next_char))
				expander_next(exp);
			if (mode == VEXPM_EXTRACT)
				ft_strncat(exp->frame->argv[exp->frame->argc],
					&exp->curr_char, 1);
			exp->len++;
		}
	}
	expander_next(exp);
}
