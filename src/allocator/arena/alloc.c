/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:44:54 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/14 13:43:48 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"

t_allocation	allocator_arena_alloc(
	t_allocator *alc, t_arena *arena, size_t size)
{
	t_allocation	alloc;
	t_arena			*temp;

	alloc.kind = ALLOC_ARENA;
	alloc.parent_id = arena->id;
	alloc.size = size;
	alloc.region = arena;
	alloc.data = NULL;
	if (arena->used + size > ARENA_CAPACITY)
	{
		temp = arena->next;
		arena->next = allocator_arena_create(alc);
		if (!arena->next)
		{
			arena->next = temp;
			return (alloc);
		}
		arena->next->next = temp;
		return (allocator_arena_alloc(alc, arena->next, size));
	}
	alloc.data = arena->data + arena->used;
	arena->used += (uint16_t)size;
	return (alloc);
}
