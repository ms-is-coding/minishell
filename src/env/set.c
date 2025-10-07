/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:27:14 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/06 17:18:50 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env_internal.h"

t_result	env_set(
	t_env *env,
	const char *key,
	const char *value,
	bool is_public)
{
	t_env_bucket	*bucket;
	t_env_bucket	*existing;

	// handle hashmap resize
	bucket = env_find_empty(env, key);
	existing = env_find_key(env, key);
	if (existing)
		bucket = existing;
	else
		env->count++;
	bucket->is_tombstone = 0;
	bucket->key = key;
	bucket->value = value;
	bucket->is_public = is_public;
	return (RESULT_OK);
}
