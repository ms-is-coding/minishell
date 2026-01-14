/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:39:19 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:32:49 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"
#include "core/stdio.h"
#include "core/string.h"

/**
 * @brief Builds an array of environment variables in the format "KEY=VALUE".
 *
 * @param env Pointer to the environment structure
 * @param arena Pointer to the arena for memory allocation
 * @return Array of strings representing the environment variables, or NULL on
 * failure.
 */
char	**env_build(t_env *env, t_arena *arena)
{
	char	**e;
	size_t	len;
	size_t	i;
	size_t	pos;

	e = allocator_alloc(env->allocator,
			sizeof(char *) * (env->count + 1), arena).data;
	if (!e)
		return (NULL);
	i = -1lu;
	pos = 0;
	while (++i < env->capacity)
	{
		if (!env->buckets[i].key || !env->buckets[i].value)
			continue ;
		len = ft_strlen(env->buckets[i].key)
			+ ft_strlen(env->buckets[i].value) + 2;
		e[pos] = allocator_alloc(env->allocator, len, arena).data;
		if (!e[pos])
			return (NULL);
		ft_snprintf(e[pos++], len, "%s=%s",
			env->buckets[i].key, env->buckets[i].value);
	}
	e[pos] = NULL;
	return (e);
}
