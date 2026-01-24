/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:10:44 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/24 16:18:06 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator_internal.h"
#include <stdlib.h>
#include <assert.h>

/**
 * @brief Allocates memory using the allocator.
 *
 * @param alc Pointer to the allocator structure
 * @param size Size of memory to allocate
 * @param arena Pointer to the arena to allocate from (optional)
 * @return t_allocation structure containing allocation details.
 */
t_allocation	allocator_alloc(t_allocator *alc, size_t size, t_arena *arena)
{
	t_allocation	alloc;

	if (arena)
		return (allocator_arena_alloc(alc, arena, size));
	if (size <= MAX_ALLOC_SIZE)
		return (allocator_slab_alloc(alc, size));
	alloc.size = size;
	alloc.kind = ALLOC_HEAP;
	alloc.data = malloc(size);
	alloc.parent_id = 0;
	alloc.region = NULL;
	return (alloc);
}
