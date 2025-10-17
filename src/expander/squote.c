/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:44:05 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/17 00:44:41 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander_internal.h"

void	expander_squote(t_expander *exp, bool dry_run)
{
	while (exp->next_char && exp->next_char != '\'')
	{
		expander_next(exp);
		if (!dry_run)
			ft_strncat(exp->frame->argv[exp->frame->argc], &exp->curr_char, 1);
		exp->len++;
	}
	expander_next(exp);
}
