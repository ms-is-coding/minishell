/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:02:57 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/16 16:07:53 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator_internal.h"
#include "allocator/slab_internal.h"

void	allocator_slab_free(t_allocation alloc)
{
	t_slab_region	*region;
	t_slab_meta		*meta;

	region = alloc.region;
	meta = (void *)((char *)alloc.data - sizeof(t_slab_meta));
	meta->prev_block |= SLAB_FLAG_FREE;
	if (region->max_free < alloc.size)
	{
		region->max_free = (uint16_t)alloc.size;
	}
}
