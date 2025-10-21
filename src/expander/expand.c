/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:33:24 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/20 16:36:47 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander_internal.h"

void	expander_expand(t_expander *exp, t_var_expansion_mode mode)
{
	int	prev_argc;

	if (mode == VEXPM_PREPARE)
		prev_argc = exp->frame->argc;
	if (exp->next_char == '~')
		expander_user(exp, mode != VEXPM_EXTRACT);
	while (exp->next_char)
	{
		expander_next(exp);
		if (exp->curr_char == '$')
			expander_var(exp, mode);
		else if (exp->curr_char == '"')
			expander_dquote(exp, mode != VEXPM_EXTRACT);
		else if (exp->curr_char == '\'')
			expander_squote(exp, mode != VEXPM_EXTRACT);
		else
			expander_char(exp, mode != VEXPM_EXTRACT);
	}
	expander_var_extract(exp, mode);
	if (mode == VEXPM_PREPARE)
		exp->frame->argc = prev_argc;
}
