/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:32:47 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/19 15:17:09 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env_internal.h"

void	env_free_bucket(t_env_bucket *bucket)
{
	if (!bucket->key || bucket->flags & ENV_FLAG_STACK)
		return ;
	if (bucket->flags & ENV_FLAG_STACK_KEY)
	{
		allocator_free_ptr((void *)(intptr_t)bucket->value);
		return ;
	}
	allocator_free_ptr((void *)(intptr_t)bucket->key);
}

// we assume that key and value are stored in a single allocation
void	env_destroy(t_env *env)
{
	size_t	i;

	i = -1ul;
	while (++i < env->capacity)
	{
		env_free_bucket(&env->buckets[i]);
	}
	allocator_free_ptr(env->buckets);
	env->capacity = 0;
	env->buckets = NULL;
}
