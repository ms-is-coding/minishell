/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:03:59 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 12:14:33 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "env/env.h"

bool	env_exists(t_env *env, const char *key)
{
	t_env_bucket	*bucket;

	bucket = env_find_key(env, key);
	if (!bucket)
		return (false);
	return (true);
}

t_result	env_set_flag(t_env *env, const char *key, t_env_flags flag)
{
	t_env_bucket	*bucket;

	bucket = env_find_key(env, key);
	if (!bucket)
		return (RESULT_ERROR);
	bucket->flags |= flag;
	return (RESULT_OK);
}

t_result	env_toggle_flag(t_env *env, const char *key, t_env_flags flag)
{
	t_env_bucket	*bucket;

	bucket = env_find_key(env, key);
	if (!bucket)
		return (RESULT_ERROR);
	bucket->flags ^= flag;
	return (RESULT_OK);
}

t_result	env_clear_flag(t_env *env, const char *key, t_env_flags flag)
{
	t_env_bucket	*bucket;

	bucket = env_find_key(env, key);
	if (!bucket)
		return (RESULT_ERROR);
	bucket->flags &= ~flag;
	return (RESULT_OK);
}
