/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:32:47 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:33:10 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env_internal.h"

/**
 * @brief Frees the resources associated with an environment bucket.
 *
 * @param bucket Pointer to the environment bucket
 */
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
/**
 * @brief Destroys the environment structure and frees associated resources.
 *
 * @param env Pointer to the environment structure
 * @note It is assumed that key and value are stored in a single allocation
 */
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
