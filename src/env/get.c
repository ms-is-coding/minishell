/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:44:20 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/06 00:55:07 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"
#include "env/env_internal.h"

const char	*env_get(t_env *env, const char *key)
{
	t_env_bucket	*bucket;

	bucket = env_find_key(env, key);
	if (!bucket)
		return (NULL);
	return (bucket->value);
}
