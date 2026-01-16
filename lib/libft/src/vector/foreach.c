/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreach.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:42:52 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 14:46:24 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/vector_internal.h"
#include "vector/vector.h"

void	vec_foreach(
	t_vec *v,
	void (*fn)(size_t, void *, void *),
	void *userdata)
{
	size_t	i;

	i = 0;
	while (i < v->length)
	{
		fn(i, v->data[(v->offset + i) % v->capacity], userdata);
		i++;
	}
}
