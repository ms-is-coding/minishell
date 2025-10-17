/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:02:15 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/17 02:32:30 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias/alias.h"
#include "common.h"
#include "libft.h"

t_result	alias_init(t_alias *alias, t_allocator *allocator)
{
	alias->capacity = MAX_ALIASES;
	alias->buckets = allocator_alloc(allocator,
			alias->capacity * sizeof(t_alias_bucket), NULL).data;
	alias->count = 0;
	alias->allocator = allocator;
	ft_memset(alias->buckets, 0, alias->capacity * sizeof(t_alias_bucket));
	return (RESULT_OK);
}
