/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:27:14 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/14 16:52:28 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias/alias_internal.h"

t_result	alias_set(
	t_alias *alias,
	const char *key,
	const char *value)
{
	t_alias_bucket	*bucket;
	t_alias_bucket	*existing;

	// handle hashmap resize
	bucket = alias_find_empty(alias, key);
	existing = alias_find_key(alias, key);
	if (existing)
		bucket = existing;
	else
		alias->count++;
	bucket->is_tombstone = 0;
	bucket->key = key;
	bucket->value = value;
	return (RESULT_OK);
}
