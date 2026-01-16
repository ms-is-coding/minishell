/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:26:55 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 17:49:12 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/vector_internal.h"
#include "vector/vector.h"

void	*vec_get(const t_vec *v, ssize_t n)
{
	if (n >= (ssize_t)v->length || n < -(ssize_t)v->length)
		return (NULL);
	if (n >= 0)
		return (v->data[((size_t)n + v->offset) % v->capacity]);
	return (v->data[(v->length + (size_t)n + v->offset) % v->capacity]);
}
