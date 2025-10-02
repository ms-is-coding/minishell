/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:27:42 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/14 13:44:10 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"

static t_slab_region	*allocator_slab_find(t_allocator *alc, size_t size)
{
	t_slab_region	*slab;
	int				i;

	i = -1;
	while (++i < STACK_SLABS)
	{
		slab = &alc->stack_slabs[i];
		if (slab->max_free >= size || slab->used + size < SLAB_CAPACITY)
			return (slab);
	}
	while (alc->slabs)
	{
		slab = alc->slabs;
		if (slab->max_free >= size || slab->used + size < SLAB_CAPACITY)
			return (slab);
		slab = slab->next;
	}
	return (NULL);
}

static void	allocator_slab_assign(t_slab_region *slab, t_allocation *alloc)
{
	t_slab_meta	*meta;

	meta = (void *)slab->data;
	if (slab->max_free >= alloc->size)
	{
		while (meta->used && meta->size < alloc->size)
			meta = (void *)((char *)meta + meta->size + sizeof(t_slab_meta));
		alloc->data = ((char *)meta + sizeof(t_slab_meta));
		meta->used = true;
		return ;
	}
	meta = (void *)(slab->data + slab->used);
	meta->used = true;
	meta->size = (uint16_t)alloc->size;
	alloc->data = slab->data + slab->used + sizeof(t_slab_meta);
	slab->used += (uint16_t)(alloc->size + sizeof(t_slab_meta));
	return ;
}

t_allocation	allocator_slab_alloc(t_allocator *alc, size_t size)
{
	t_allocation	alloc;
	t_slab_region	*slab;

	alloc.size = size;
	alloc.kind = ALLOC_SLAB;
	alloc.data = NULL;
	slab = allocator_slab_find(alc, size);
	if (slab)
	{
		allocator_slab_assign(slab, &alloc);
		return (alloc);
	}
	slab = allocator_slab_create(alc);
	if (!slab)
		return (alloc);
	slab->used = 0;
	slab->max_free = 0;
	slab->id = alc->next_slab_id++;
	slab->next = alc->slabs;
	alc->slabs = slab->next;
	return (alloc);
}
