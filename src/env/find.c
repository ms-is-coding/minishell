/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:49:43 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/21 17:02:50 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "env/env_internal.h"

#define UNREACHABLE NULL

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
