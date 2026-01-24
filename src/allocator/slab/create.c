/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 00:25:37 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/24 16:17:44 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"

/**
 * @brief Creates a new slab region within the allocator.
 *
 * @param alc Pointer to the allocator instance
 * @return Pointer to the newly created slab region, or NULL on failure.
 */
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
