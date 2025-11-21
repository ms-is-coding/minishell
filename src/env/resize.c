/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:54:25 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/21 17:02:14 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env_internal.h"
#include <stddef.h>

static inline size_t	scale_1_5_fast(size_t x)
{
	return (x + (x >> 1));
}

t_result	env_resize(t_env *env)
{
	t_env_bucket	*old_buckets;
	size_t			old_capacity;
	size_t			i;

	old_buckets = env->buckets;
	old_capacity = env->capacity;
	env->capacity = scale_1_5_fast(env->capacity);
	env->buckets = allocator_calloc(env->capacity, sizeof(t_env_bucket));
	if (!env->buckets)
		return (RESULT_ERROR);
	env->count = 0;
	i = -1lu;
	while (++i < old_capacity)
	{
		if (!old_buckets[i].key)
			continue ;
		env_set(env, old_buckets[i].key,
			old_buckets[i].value, old_buckets[i].flags);
	}
	allocator_free_ptr(old_buckets);
	return (RESULT_OK);
}
