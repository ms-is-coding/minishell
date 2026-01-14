/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:54:25 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:10:42 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env_internal.h"
#include <stddef.h>

/**
 * @brief Scales the given size by 1.5 using a fast method.
 *
 * @param x The size to scale
 * @return The scaled size.
 */
static inline size_t	scale_1_5_fast(size_t x)
{
	return (x + (x >> 1));
}

/**
 * @brief Resizes the environment's bucket array to accommodate more entries.
 *
 * @param env Pointer to the environment structure
 * @return RESULT_OK on success, RESULT_ERROR on failure.
 */
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
