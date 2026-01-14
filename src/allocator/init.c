/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:57:35 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:27:13 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator_internal.h"
#include <stdint.h>
#include <assert.h>

/**
 * @brief Initializes the custom memory allocator.
 *
 * @param alc Pointer to the allocator to initialize
 */
void	allocator_init(t_allocator *alc)
{
	int	i;

	alc->next_arena_id = 1;
	alc->next_slab_id = 1;
	alc->slabs = NULL;
	alc->arenas = NULL;
	i = -1;
	while (++i < STACK_ARENAS)
	{
		alc->stack_arenas[i].id = 0;
		alc->stack_arenas[i].used = 0;
		alc->stack_arenas[i].next = alc->arenas;
		alc->arenas = &alc->stack_arenas[i];
	}
	i = -1;
	while (++i < STACK_SLABS)
	{
		alc->stack_slabs[i].id = 0;
		alc->stack_slabs[i].max_free = 0;
		alc->stack_slabs[i].used = 0;
		alc->stack_slabs[i].next = alc->slabs;
		alc->slabs = &alc->stack_slabs[i];
	}
	__attribute__((__unused__)) void *_;
	_ = get_allocator(alc);
}

/**
 * @brief Retrieves the global allocator instance.
 *
 * @param alc Pointer to the allocator to set as the global instance, or NULL
 * to retrieve the current instance
 * @return Pointer to the global allocator instance.
 */
__attribute__((__warn_unused_result__))
t_allocator	*get_allocator(t_allocator *alc)
{
	static t_allocator	*save = NULL;

	if (alc)
		save = alc;
	assert(save != NULL);
	return (save);
}
