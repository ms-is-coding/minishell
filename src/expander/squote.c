/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:44:05 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/15 11:56:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander_internal.h"
#include "core/string.h"

/**
 * @brief Expands single-quoted strings.
 *
 * @param exp Pointer to the expander
 * @param mode The variable expansion mode
 */
void	expander_squote(t_expander *exp, t_var_expansion_mode mode)
{
	exp->force_extract = true;
	while (exp->next_char && exp->next_char != '\'')
	{
		expander_next(exp);
		if (mode == VEXPM_EXTRACT)
			ft_strncat(exp->frame->argv[exp->frame->argc], &exp->curr_char, 1);
		exp->len++;
	}
	expander_next(exp);
}
