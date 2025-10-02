/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:10:44 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/13 18:23:13 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"
#include <stdlib.h>

t_allocation	allocator_alloc(t_allocator *alc, size_t size, t_arena *arena)
{
	t_allocation	alloc;

	if (arena)
		return (allocator_arena_alloc(alc, arena, size));
	if (size <= MAX_SLAB_SIZE)
		return (allocator_slab_alloc(alc, size));
	alloc.size = size;
	alloc.kind = ALLOC_ALLOC;
	alloc.data = malloc(size);
	alloc.parent_id = 0;
	alloc.region = NULL;
	return (alloc);
}
