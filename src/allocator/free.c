/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:01:08 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 13:18:36 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include <stdlib.h>
#include <assert.h>

/**
 * @brief Frees the given allocation based on its kind.
 *
 * @param alc Pointer to the allocator instance
 * @param alloc The allocation to be freed
 */
void	allocator_free(t_allocator *alc, t_allocation alloc)
{
	(void)alc;
	assert(alloc.kind != ALLOC_ARENA);
	if (alloc.kind == ALLOC_HEAP)
		free(alloc.data);
}
