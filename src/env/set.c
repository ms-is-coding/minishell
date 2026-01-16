/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:27:14 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 17:03:27 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"
#include "env/env_internal.h"

/**
 * @brief Sets an environment variable in the environment.
 *
 * @param env Pointer to the environment
 * @param key The key of the environment variable
 * @param value The value of the environment variable
 * @param flags Flags for the environment variable
 * @return RESULT_OK on success, RESULT_ERROR on failure, RESULT_RDONLY if the
 * variable is read-only.
 */
t_result	env_set(
	t_env *env,
	const char *key,
	const char *value,
	t_env_flags flags)
{
	t_env_bucket	*bucket;
	t_env_bucket	*existing;

	bucket = env_find_empty(env, key);
	existing = env_find_key(env, key);
	if (existing)
		bucket = existing;
	else
		env->count++;
	if (!bucket)
		return (RESULT_ERROR);
	if (bucket->flags & ENV_FLAG_RDONLY)
		return (RESULT_RDONLY);
	bucket->is_tombstone = 0;
	env_free_bucket(bucket);
	bucket->key = key;
	bucket->value = value;
	bucket->flags = flags;
	return (RESULT_OK);
}
