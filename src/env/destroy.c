/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:32:47 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/14 11:23:59 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"

// we assume that key and value are in a single allocation
void	env_destroy(t_env *env)
{
	size_t			i;
	t_env_bucket	*bucket;

	i = -1ul;
	while (++i < env->capacity)
	{
		bucket = &env->buckets[i];
		if (!bucket->key || bucket->flags & ENV_FLAG_STACK)
			continue ;
		if (bucket->flags & ENV_FLAG_STACK_KEY)
		{
			allocator_free_ptr((void *)bucket->value);
			continue ;
		}
		allocator_free_ptr((void *)bucket->key);
	}
	allocator_free_ptr(env->buckets);
	env->capacity = 0;
	env->buckets = NULL;
}
