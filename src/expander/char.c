/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:05:45 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/17 01:35:20 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander_internal.h"
#include "libft.h"

void	expander_char(t_expander *exp, bool dry_run)
{
	if (exp->curr_char == '\\')
		expander_next(exp);
	if (!dry_run)
		ft_strncat(exp->frame->argv[exp->frame->argc], &exp->curr_char, 1);
	exp->len++;
}
