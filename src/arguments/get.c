/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:17:53 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/02 20:33:39 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"

_Bool	arguments_is_set(t_arguments *args, const char *name)
{
	auto const t_argument * arg = arguments_find(args, name);
	if (!arg)
		return (0);
	return (arg->is_set);
}

char	*arguments_get(t_arguments *args, const char *name)
{
	auto const t_argument * arg = arguments_find(args, name);
	if (!arg)
		return (NULL);
	return (arg->value);
}
