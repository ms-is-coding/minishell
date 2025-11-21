/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:27:14 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/21 17:03:11 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env_internal.h"

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
