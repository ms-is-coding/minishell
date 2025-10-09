/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:47:51 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/09 12:48:39 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias/alias_internal.h"

void	alias_remove(t_alias *alias, const char *key)
{
	t_alias_bucket	*bucket;

	bucket = alias_find_key(alias, key);
	if (!bucket)
		return ;
	bucket->key = NULL;
	bucket->value = NULL;
	bucket->is_tombstone = 1;
}
