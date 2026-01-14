/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:44:54 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 15:32:39 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Allocates a large block of memory outside of the arena system.
 *
 * @param arena Pointer to the arena structure
 * @param size Size of memory to allocate
 * @return t_allocation structure containing allocation details
 */
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

/**
 * @brief Finds a suitable arena for allocation.
 *
 * @param alc Pointer to the allocator structure
 * @param arena Pointer to the starting arena
 * @param size Size of memory to allocate
 * @return Pointer to the suitable arena, or NULL on failure.
 */
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

/**
 * @brief Allocates memory from a specified arena.
 *
 * @param alc Pointer to the allocator structure
 * @param arena Pointer to the arena to allocate from
 * @param size Size of memory to allocate
 */
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
