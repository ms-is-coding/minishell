/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:03:18 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/13 17:04:18 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "alias/alias.h"
#include "libft.h"

static void	alias_sort(t_alias_bucket **buckets, size_t size)
{
	t_alias_bucket	*temp;
	size_t	i;

	i = 0;
	while (i + 1 < size)
	{
		if (ft_strcmp(buckets[i]->key, buckets[i + 1]->key) > 0)
		{
			temp = buckets[i + 1];
			buckets[i + 1] = buckets[i];
			buckets[i] = temp;
			i = 0;
		}
		else
			i++;
	}
}

t_result	alias_print(t_alias *alias, const char *key)
{
	const char	*value; 

	if (!key)
		return (RESULT_ERROR);
	value = alias_get(alias, key);
	if (value)
	{
		ft_printf("alias %s='%s'\n", key, value);
		return (RESULT_OK);
	}
	else
		return (RESULT_ERROR);
}

void	alias_print_all(t_alias *alias)
{
	size_t			count;
	size_t			i;
	t_alias_bucket	*buckets[alias->capacity]; //overkill ?

	count = 0;
	i = 0;
	while (i < alias->capacity)
	{
		if (alias->buckets[i].key && !alias->buckets[i].is_tombstone)
			buckets[count++] = &alias->buckets[i];
		i++;
	}
	alias_sort(buckets, count);
	i = 0;
	while (i < count)
	{
		ft_printf("alias %s='%s'\n", buckets[i]->key, buckets[i]->value);
		i++;
	}
}
