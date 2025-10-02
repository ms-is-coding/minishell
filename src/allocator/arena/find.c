/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:43:29 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/13 17:01:19 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"

t_arena	*allocator_arena_find(t_allocator *alc, t_arena_id id)
{
	t_arena	*arena;
	int		i;

	if (id == 0)
		return (NULL);
	i = -1;
	while (++i < STACK_ARENAS)
	{
		if (alc->stack_arenas[i].id == id)
			return (&alc->stack_arenas[i]);
	}
	arena = alc->arenas;
	while (arena)
	{
		if (arena->id == id)
			return (arena);
	}
	return (NULL);
}
