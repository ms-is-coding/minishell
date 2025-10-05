/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 00:25:37 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/16 17:35:43 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"

t_slab_region	*allocator_slab_create(t_allocator *alc)
{
	t_slab_region	*slab;

	slab = allocator_alloc(alc, sizeof(t_slab_region), NULL).data;
	if (!slab)
		return (NULL);
	slab->id = alc->next_slab_id++;
	slab->max_free = 0;
	slab->used = 0;
	slab->next = alc->slabs;
	alc->slabs = slab;
	return (slab);
}
