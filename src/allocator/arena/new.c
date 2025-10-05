/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:58:31 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/03 00:46:34 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"
#include <stdint.h>

t_arena	*allocator_arena_new(t_allocator *alc)
{
	t_arena	*arena;

	arena = alc->arenas;
	while (arena)
	{
		if (!is_arena_active(arena))
		{
			arena->id |= ARENA_FLAG_ACTIVE;
			return (arena);
		}
		arena = arena->next;
	}
	arena = allocator_arena_create(alc);
	if (!arena)
		return (NULL);
	arena->id = ARENA_FLAG_ACTIVE | (alc->next_arena_id++);
	arena->used = 0;
	arena->next = alc->arenas;
	alc->arenas = arena;
	return (arena);
}
