/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   every.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:49:59 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 14:51:16 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/vector_internal.h"
#include "vector/vector.h"

bool	vec_every(t_vec *v, bool (*fn)(size_t, void *, void *), void *userdata)
{
	size_t	i;

	i = 0;
	while (i < v->length)
	{
		if (!fn(i, v->data[(v->offset + i) % v->capacity], userdata))
			return (false);
		i++;
	}
	return (true);
}
