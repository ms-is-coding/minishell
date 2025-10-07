/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:47:51 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/06 01:01:34 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env_internal.h"

void	env_remove(t_env *env, const char *key)
{
	t_env_bucket	*bucket;

	bucket = env_find_key(env, key);
	if (!bucket)
		return ;
	bucket->key = NULL;
	bucket->value = NULL;
	bucket->is_tombstone = 1;
}
