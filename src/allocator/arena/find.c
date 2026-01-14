/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:43:29 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:25:28 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"

/**
 * @brief Finds a memory arena by its ID within the allocator.
 *
 * @param alc Pointer to the allocator managing the arenas
 * @param id The ID of the arena to find
 * @return Pointer to the found arena, or NULL if not found
 */
t_arena	*allocator_arena_find(t_allocator *alc, t_arena_id id)
{
	t_arena	*arena;

	if (id == 0)
		return (NULL);
	arena = alc->arenas;
	while (arena)
	{
		if (arena->id == id)
			return (arena);
	}
	return (NULL);
}
