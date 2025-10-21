/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:47:51 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/21 22:36:43 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"

t_result	env_remove(t_env *env, const char *key)
{
	t_env_bucket	*bucket;

	bucket = env_find_key(env, key);
	if (!bucket)
		return (RESULT_ERROR);
	if (bucket->flags & ENV_FLAG_RDONLY)
		return (RESULT_RDONLY);
	bucket->key = NULL;
	bucket->value = NULL;
	bucket->is_tombstone = 1;
	bucket->flags = 0;
	return (RESULT_OK);
}
