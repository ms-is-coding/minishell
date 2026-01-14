/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:49:43 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:10:21 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "env/env_internal.h"
#include "core/string.h"

#define UNREACHABLE NULL

/**
 * @brief Finds the bucket associated with a given key in the environment.
 *
 * @param env Pointer to the environment structure
 * @param key The key to search for
 * @return Pointer to the bucket if found, or NULL if the key does not exist.
 */
t_env_bucket	*env_find_key(t_env *env, const char *key)
{
	size_t			i;
	t_env_bucket	*bucket;

	i = env_hash(env, key);
	bucket = &env->buckets[i];
	while (bucket)
	{
		bucket = &env->buckets[i];
		if (!bucket->key)
		{
			if (!bucket->is_tombstone)
				return (NULL);
		}
		else if (ft_strcmp(key, bucket->key) == 0)
			return (bucket);
		i = (i + 1) % env->capacity;
	}
	return (UNREACHABLE);
}

/**
 * @brief Finds an empty bucket for a given key in the environment.
 *
 * @param env Pointer to the environment structure
 * @param key The key to find an empty bucket for
 * @return Pointer to the empty bucket, or NULL on failure.
 */
t_env_bucket	*env_find_empty(t_env *env, const char *key)
{
	size_t			i;
	t_env_bucket	*bucket;

	if ((float)env->count / (float)env->capacity > ENV_THRESHOLD)
	{
		if (env_resize(env) != RESULT_OK)
			return (NULL);
	}
	i = env_hash(env, key);
	bucket = &env->buckets[i];
	while (bucket)
	{
		bucket = &env->buckets[i];
		if (!bucket->key)
			return (bucket);
		i = (i + 1) % env->capacity;
	}
	return (UNREACHABLE);
}
