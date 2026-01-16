/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:51:27 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 14:52:33 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/vector_internal.h"
#include "vector/vector.h"

bool	vec_some(t_vec *v, bool (*fn)(size_t, void *, void *), void *userdata)
{
	size_t	i;

	i = 0;
	while (i < v->length)
	{
		if (fn(i, v->data[(v->offset + i) % v->capacity], userdata))
			return (true);
		i++;
	}
	return (false);
}
