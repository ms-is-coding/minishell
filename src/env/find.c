/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:49:43 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 12:43:24 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "env/env.h"
#include "env/env_internal.h"
#include "core/string.h"
#include "core/stdio.h"

static const char *get_color(const char *ptr)
{
	int index = ((uint64_t)ptr) % 14;

	return (const char *[]){
		"\x1b[31m",
		"\x1b[32m",
		"\x1b[33m",
		"\x1b[34m",
		"\x1b[35m",
		"\x1b[36m",
		"\x1b[37m",
		"\x1b[30;41m",
		"\x1b[30;42m",
		"\x1b[30;43m",
		"\x1b[30;44m",
		"\x1b[30;45m",
		"\x1b[30;46m",
		"\x1b[30;47m",
	}[index];
}

static void	print_env(t_env *e)
{
	return ;
	; ft_dprintf(2, "\x1b[93m==> ENV <==\x1b[m\n");
	for (size_t i = 0; i < e->capacity; i++)
	{
		t_env_bucket	*b = &e->buckets[i];
		ft_dprintf(2, "%s%p\x1b[m [\"%s\" = \"%.32s\", flags=%i] %s%p\x1b[m\n",
			b->is_tombstone ? "\x1b[91m" : b->value ? "\x1b[92m" : "",
			b, b->key, b->value, b->flags, get_color(b->key), b->key);
	}
}

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
	print_env(env);
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
	__builtin_unreachable();
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
	__builtin_unreachable();
}
