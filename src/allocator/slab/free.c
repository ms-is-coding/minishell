/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:02:57 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:26:39 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator_internal.h"
#include "allocator/slab_internal.h"

/**
 * @brief Frees a slab allocation.
 *
 * @param alloc The allocation to free
 */
void	allocator_slab_free(t_allocation alloc)
{
	t_slab_region	*region;
	t_slab_meta		*meta;

	region = alloc.region;
	meta = (void *)((char *)alloc.data - sizeof(t_slab_meta));
	meta->prev_block |= SLAB_FLAG_FREE;
	if (region->max_free < meta->size)
	{
		region->max_free = (uint16_t)meta->size;
	}
}
