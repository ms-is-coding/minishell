/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:44:54 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 12:54:24 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

static t_allocation	large_alloc(t_arena *arena, size_t size)
{
	t_large_alloc	*large;
	t_allocation	alloc;
	size_t			total_size;

	total_size = sizeof(t_large_alloc) + size;
	alloc.data = NULL;
	large = malloc(total_size);
	if (!large)
		return (alloc);
	large->id = arena->id | ARENA_FLAG_LARGE;
	large->data = (void *)((char *)large + sizeof(t_large_alloc));
	large->next = arena->next;
	arena->next = (void *)large;
	alloc.kind = ALLOC_ARENA;
	alloc.size = size;
	alloc.data = large->data;
	alloc.parent_id = arena->id;
	alloc.region = (void *)large;
	return (alloc);
}

static t_arena	*find_arena(t_allocator *alc, t_arena *arena, size_t size)
{
	t_arena	*candidate;

	candidate = arena;
	while (candidate)
	{
		if (is_arena(candidate) && !is_arena_active(candidate))
		{
			candidate->id = arena->id | ARENA_FLAG_ACTIVE;
			return (candidate);
		}
		if (is_arena(candidate) && candidate->used + size <= ARENA_CAPACITY)
			return (candidate);
		candidate = candidate->next;
	}
	candidate = allocator_arena_create(alc);
	if (!candidate)
		return (NULL);
	candidate->next = arena->next;
	arena->next = candidate;
	candidate->id = arena->id;
	candidate->used = 0;
	return (candidate);
}

t_allocation	allocator_arena_alloc(
	t_allocator *alc, t_arena *arena, size_t size)
{
	t_allocation	alloc;
	size_t			real_size;

	if (size > MAX_ALLOC_SIZE)
		return (large_alloc(arena, size));
	real_size = (size + 7) & ~7LU;
	alloc.kind = ALLOC_ARENA;
	alloc.parent_id = arena->id;
	alloc.size = real_size;
	alloc.data = NULL;
	arena = find_arena(alc, arena, real_size);
	if (!arena)
		return (alloc);
	alloc.region = arena;
	alloc.data = arena->data + arena->used;
	arena->used += (uint16_t)real_size;
	return (alloc);
}
