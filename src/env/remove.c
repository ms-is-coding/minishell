/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:47:51 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/17 09:50:12 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env_internal.h"

t_result	env_remove(t_env *env, const char *key)
{
	t_env_bucket	*bucket;

	bucket = env_find_key(env, key);
	if (!bucket)
		return (RESULT_ERROR); 
	bucket->key = NULL;
	bucket->value = NULL;
	bucket->is_tombstone = 1;
	return (RESULT_OK);
}
