/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:44:35 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 14:47:19 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/vector_internal.h"
#include "vector/vector.h"
#include <stddef.h>

void	vec_map(t_vec *v, void *(*fn)(size_t, void *, void *), void *userdata)
{
	size_t	i;
	void	**cell;

	i = 0;
	while (i < v->length)
	{
		cell = v->data + (v->offset + i) % v->capacity;
		*cell = fn(i, *cell, userdata);
		i++;
	}
}
