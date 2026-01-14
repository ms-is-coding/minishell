/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:13:50 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:25:47 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"
#include <stdlib.h>

/**
 * @brief Frees the given arena and its associated memory blocks.
 *
 * @param alc Pointer to the allocator instance
 * @param arena Pointer to the arena to be freed
 */
void	allocator_arena_free(t_allocator *alc, t_arena *arena)
{
	t_arena	*temp;
	t_arena	*prev;

	(void)alc;
	prev = arena;
	while (arena)
	{
		temp = arena->next;
		if (!is_arena(arena))
		{
			free(arena);
			prev->next = temp;
			arena = temp;
			continue ;
		}
		arena->used = 0;
		arena->id &= (uint16_t)(~ARENA_FLAG_ACTIVE);
		prev = arena;
		arena = temp;
	}
}
