/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:05:45 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/23 19:38:11 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander_internal.h"

void	expander_char(t_expander *exp, t_var_expansion_mode mode)
{
	if (exp->curr_char == '\\')
		expander_next(exp);
	if (mode == VEXPM_EXTRACT)
		ft_strncat(exp->frame->argv[exp->frame->argc], &exp->curr_char, 1);
	exp->len++;
}
