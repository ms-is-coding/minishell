/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:27:42 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/24 16:17:52 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator_internal.h"
#include "allocator/slab_internal.h"

/**
 * @brief Finds a suitable slab region for the allocation.
 *
 * @param alc Pointer to the allocator structure
 * @param size Size of memory to allocate
 * @return Pointer to the suitable slab region, or NULL on failure.
 */
static t_slab_region	*allocator_slab_find(t_allocator *alc, size_t size)
{
	t_slab_region	*slab;

	slab = alc->slabs;
	while (slab)
	{
		if (slab->max_free >= size || slab->used + size < SLAB_CAPACITY)
			return (slab);
		slab = slab->next;
	}
	return (allocator_slab_create(alc));
}

/**
 * @brief Assigns a slab region to the allocation.
 *
 * @param slab Pointer to the slab region
 * @param alloc Pointer to the allocation structure
 */
static void	allocator_slab_assign(t_slab_region *slab, t_allocation *alloc)
{
	t_slab_meta	*meta;

	meta = (void *)slab->data;
	if (slab->max_free >= alloc->size)
	{
		while (!is_slab_free(meta) && meta->size < alloc->size)
			meta = (void *)((char *)meta + meta->size);
		alloc->data = ((char *)meta + sizeof(t_slab_meta));
		alloc->region = slab;
		alloc->parent_id = slab->id;
		meta->prev_block &= (uint16_t)(~SLAB_FLAG_FREE);
		return ;
	}
	meta = (void *)(slab->data + slab->used);
	meta->prev_block &= (uint16_t)(~SLAB_FLAG_FREE);
	meta->size = (uint16_t)alloc->size;
	alloc->data = slab->data + slab->used + sizeof(t_slab_meta);
	alloc->region = slab;
	alloc->parent_id = slab->id;
	slab->used += (uint16_t)(alloc->size + sizeof(t_slab_meta));
	return ;
}

/**
 * @brief Allocates memory from the slab allocator.
 *
 * @param alc Pointer to the allocator structure
 * @param size Size of memory to allocate
 * @return t_allocation structure containing allocation details.
 */
t_allocation	allocator_slab_alloc(t_allocator *alc, size_t size)
{
	t_allocation	alloc;
	t_slab_region	*slab;

	alloc.size = (size + 7) & ~7LU;
	alloc.kind = ALLOC_SLAB;
	alloc.data = NULL;
	alloc.region = NULL;
	alloc.parent_id = 0;
	slab = allocator_slab_find(alc, alloc.size);
	if (!slab)
		return (alloc);
	allocator_slab_assign(slab, &alloc);
	return (alloc);
}
