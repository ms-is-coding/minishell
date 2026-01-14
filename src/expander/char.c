/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:05:45 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 16:26:54 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander_internal.h"
#include "core/string.h"

/**
 * @brief Handles a single character during expansion.
 *
 * @param exp Pointer to the expander
 * @param mode The variable expansion mode
 */
void	expander_char(t_expander *exp, t_var_expansion_mode mode)
{
	if (exp->curr_char == '\\')
		expander_next(exp);
	if (mode == VEXPM_EXTRACT)
		ft_strncat(exp->frame->argv[exp->frame->argc], &exp->curr_char, 1);
	exp->len++;
}
