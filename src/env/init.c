/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:02:15 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/21 17:36:50 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"
#include "common.h"
#include "util/exec.h"
#include "libft.h"
#include <string.h>

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
	char	*tmp;

	if (!env_get(env, "PATH"))
		env_set(env, "PATH", DEFAULT_PATH,
			ENV_FLAG_EXPORT | ENV_FLAG_STACK_KEY);
	tmp = exec_with_output((char *[]){
			(char *)(intptr_t)"/usr/bin/id",
			(char *)(intptr_t)"-u", NULL});
	if (!tmp)
		return ;
	tmp[ft_strlen(tmp) - 1] = '\0';
	env_set(env, "UID", allocator_strdup(tmp),
		ENV_FLAG_RDONLY | ENV_FLAG_INTEGER | ENV_FLAG_STACK_KEY);
	ft_free(tmp);
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
	env->buckets = allocator_calloc(env->capacity, sizeof(t_env_bucket));
	if (!env->buckets)
		return (RESULT_ERROR);
	env->count = 0;
	env->allocator = allocator;
	while (envp[i])
	{
		entry = allocator_strdup(envp[i]);
		if (!entry)
			continue ;
		value = ft_strchr(entry, '=');
		value[0] = '\0';
		value++;
		env_set(env, entry, value, ENV_FLAG_EXPORT);
		i++;
	}
	env_init_default_values(env);
	return (RESULT_OK);
}
