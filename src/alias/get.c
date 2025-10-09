/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:44:20 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/09 12:40:12 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias/alias.h"
#include "alias/alias_internal.h"

const char	*alias_get(t_alias *alias, const char *key)
{
	t_alias_bucket	*bucket;

	bucket = alias_find_key(alias, key);
	if (!bucket)
		return (NULL);
	return (bucket->value);
}
