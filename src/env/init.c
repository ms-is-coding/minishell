/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:02:15 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/21 23:24:23 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"
#include "common.h"
#include "libft.h"

static size_t	envp_count(char **envp)
{
	size_t	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

static void	env_init_default_values(t_env *env)
{
	if (!env_get(env, "PATH"))
		env_set(env, "PATH", DEFAULT_PATH, ENV_FLAG_EXPORT);
}

static inline size_t	scale_1_25_fast(size_t x)
{
	return (x + (x >> 2));
}

t_result	env_init(t_env *env, t_allocator *allocator, char **envp)
{
	size_t	i;
	char	*value;
	char	*entry;

	i = 0;
	env->capacity = scale_1_25_fast(envp_count(envp));
	env->buckets = allocator_alloc(allocator,
			env->capacity * sizeof(t_env_bucket), NULL).data;
	env->count = 0;
	env->allocator = allocator;
	ft_memset(env->buckets, 0, env->capacity * sizeof(t_env_bucket));
	while (envp[i])
	{
		entry = ft_strdup(envp[i]);
		value = ft_strchr(entry, '=');
		value[0] = '\0';
		value++;
		env_set(env, entry, value, ENV_FLAG_EXPORT);
		i++;
	}
	env_init_default_values(env);
	return (RESULT_OK);
}
