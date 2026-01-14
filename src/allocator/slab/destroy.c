/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:29:20 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:26:36 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator_internal.h"
#include <stdlib.h>

/**
 * @brief Destroys a slab region and frees its memory if it's not a stack slab.
 *
 * @param alc Pointer to the allocator
 * @param slab Pointer to the slab region to destroy
 */
void	allocator_slab_destroy(t_allocator *alc, t_slab_region *slab)
{
	slab->id = 0;
	slab->used = 0;
	if (slab >= alc->stack_slabs && slab < alc->stack_slabs + STACK_SLABS)
		return ;
	free(slab);
}
