/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:27:42 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/16 17:35:52 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator_internal.h"
#include "allocator/slab_internal.h"

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

static void	allocator_slab_assign(t_slab_region *slab, t_allocation *alloc)
{
	t_slab_meta	*meta;

	meta = (void *)slab->data;
	if (slab->max_free >= alloc->size)
	{
		while (!is_slab_free(meta) && meta->size < alloc->size)
			meta = (void *)((char *)meta + meta->size + sizeof(t_slab_meta));
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
