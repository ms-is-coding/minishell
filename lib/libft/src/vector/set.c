/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:28:29 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 14:26:38 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/vector_internal.h"
#include "vector/vector.h"

t_vec_result	vec_set(t_vec *v, size_t idx, void *value)
{
	if (idx > v->length)
		return (VEC_ERR_BOUNDS);
	v->data[idx] = value;
	return (VEC_OK);
}
