/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:58:31 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 15:28:44 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"
#include <stdint.h>

/**
 * @brief Creates a new arena for the allocator.
 *
 * @param alc Pointer to the allocator structure
 * @return Pointer to the newly created arena, or NULL on failure.
 */
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
