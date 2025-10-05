/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:01:08 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/15 14:24:56 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator_internal.h"
#include <stdlib.h>
#include <assert.h>

void	allocator_free(t_allocator *alc, t_allocation alloc)
{
	(void)alc;
	assert(alloc.kind != ALLOC_ARENA);
	if (alloc.kind == ALLOC_HEAP)
		free(alloc.data);
	if (alloc.kind == ALLOC_SLAB)
		allocator_slab_free(alloc);
}
