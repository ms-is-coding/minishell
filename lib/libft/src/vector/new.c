/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:04:58 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 16:24:16 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/vector_internal.h"
#include "vector/vector.h"
#include <stdlib.h>

t_vec	*vec_new(size_t initial_capacity)
{
	t_vec	*vec;

	vec = malloc(sizeof(t_vec));
	if (!vec)
		return (NULL);
	vec->data = malloc(initial_capacity * sizeof(void *));
	if (!vec->data)
	{
		free(vec);
		return (NULL);
	}
	vec->capacity = initial_capacity;
	vec->length = 0;
	vec->offset = 0;
	return (vec);
}
