/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:59:35 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:25:12 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator_internal.h"
#include <stdlib.h>

/**
 * @brief Destroys a memory arena and frees its resources.
 *
 * @param alc Pointer to the allocator managing the arena
 * @param arena Pointer to the arena to destroy.
 */
void	allocator_arena_destroy(t_allocator *alc, t_arena *arena)
{
	arena->id = 0;
	arena->used = 0;
	if (arena >= alc->stack_arenas && arena < alc->stack_arenas + STACK_ARENAS)
		return ;
	free(arena);
}
