/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:44:20 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 15:44:41 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"
#include "env/env_internal.h"


/**
 * @brief Retrieves the value associated with a given key in the environment.
 *
 * @param env Pointer to the environment structure
 * @param key The key whose value is to be retrieved
 * @return The value associated with the key, or NULL if the key does not exist.
 */
const char	*env_get(t_env *env, const char *key)
{
	t_env_bucket	*bucket;

	bucket = env_find_key(env, key);
	if (!bucket)
		return (NULL);
	return (bucket->value);
}
