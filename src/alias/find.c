/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:49:43 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/14 17:01:47 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias/alias_internal.h"

#define UNREACHABLE NULL

t_alias_bucket	*alias_find_key(t_alias *alias, const char *key)
{
	size_t			i;
	t_alias_bucket	*bucket;

	i = alias_hash(alias, key);
	bucket = &alias->buckets[i];
	while (bucket)
	{
		bucket = &alias->buckets[i];
		if (!bucket->key)
		{
			if (!bucket->is_tombstone)
				return (NULL);
		}
		else if (ft_strcmp(key, bucket->key) == 0)
			return (bucket);
		i = (i + 1) % alias->capacity;
	}
	return (UNREACHABLE);
}

t_alias_bucket	*alias_find_empty(t_alias *alias, const char *key)
{
	size_t			i;
	t_alias_bucket	*bucket;

	i = alias_hash(alias, key);
	bucket = &alias->buckets[i];
	while (bucket)
	{
		bucket = &alias->buckets[i];
		if (!bucket->key)
			return (bucket);
		i = (i + 1) % alias->capacity;
	}
	return (UNREACHABLE);
}
