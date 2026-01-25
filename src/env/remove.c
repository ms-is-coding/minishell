/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:47:51 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/24 15:08:28 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"
#include "env/env_internal.h"

/**
 * @brief Removes an environment variable from the environment.
 *
 * @param env Pointer to the environment structure
 * @param key The key of the environment variable to remove
 * @return RESULT_OK on success, RESULT_ERROR if the key does not exist,
 * RESULT_RDONLY if the variable is read-only.
 */
t_result	env_remove(t_env *env, const char *key)
{
	t_env_bucket	*bucket;

	bucket = env_find_key(env, key);
	if (!bucket)
		return (RESULT_ERROR);
	if (bucket->flags & ENV_FLAG_RDONLY)
		return (RESULT_RDONLY);
	env_free_bucket(bucket);
	bucket->key = NULL;
	bucket->value = NULL;
	bucket->is_tombstone = 1;
	bucket->flags = 0;
	return (RESULT_OK);
}
