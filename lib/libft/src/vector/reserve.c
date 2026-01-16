/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:26:07 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 15:59:27 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"
#include "vector/vector_internal.h"
#include "vector/vector.h"
#include <string.h>

t_vec_result	vec_reserve(t_vec *v, size_t capacity)
{
	void	*save_ptr;
	void	*new_data;
	size_t	real_offset;

	if (capacity <= v->capacity)
		return (VEC_OK);
	new_data = malloc(capacity * sizeof(void *));
	if (!new_data)
		return (VEC_OOM);
	real_offset = v->offset % v->capacity;
	save_ptr = ft_mempcpy(new_data, v->data + real_offset,
			sizeof(void *) * (v->capacity - real_offset));
	ft_memcpy(save_ptr, v->data, sizeof(void *) * real_offset);
	free(v->data);
	v->data = new_data;
	v->capacity = capacity;
	v->offset = 0;
	return (VEC_OK);
}
