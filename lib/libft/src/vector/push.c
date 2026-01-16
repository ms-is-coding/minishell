/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:42:48 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 15:59:13 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/vector.h"
#include "vector/vector_internal.h"

static inline size_t	scale_fast(size_t capacity)
{
	return (capacity + (capacity >> 1));
}

t_vec_result	vec_push(t_vec *v, void *value)
{
	if (v->length == v->capacity
		&& vec_reserve(v, scale_fast(v->capacity)) != VEC_OK)
		return (VEC_OOM);
	v->data[(v->length++ + v->offset) % v->capacity] = value;
	return (VEC_OK);
}
