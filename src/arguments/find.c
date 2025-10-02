/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:10:31 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 13:23:56 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include "libft.h"

t_argument	*arguments_find(t_arguments *args, const char *name)
{
	static t_argument	dummy = {NULL, NULL, 0, 0, 0};
	size_t				i;

	i = (size_t)-1;
	while (++i < args->options.length)
	{
		auto t_value val = ft_vector_at(&args->options, (ssize_t)i);
		if (val.type != TYPE_UNDEFINED && val.value.ptr)
		{
			auto t_argument * arg = val.value.ptr;
			if (arg && arg->long_name && ft_strcmp(arg->long_name, name) == 0)
				return (arg);
		}
	}
	return (&dummy);
}

t_argument	*arguments_find_short(t_arguments *args, char name)
{
	static t_argument	dummy = {NULL, NULL, 0, 0, 0};
	size_t				i;

	i = (size_t)-1;
	while (++i < args->options.length)
	{
		auto t_value val = ft_vector_at(&args->options, (ssize_t)i);
		if (val.type != TYPE_UNDEFINED && val.value.ptr)
		{
			auto t_argument * arg = val.value.ptr;
			if (arg && arg->short_name == name)
				return (val.value.ptr);
		}
	}
	return (&dummy);
}
