/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:58:31 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/13 18:25:03 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"
#include <stdint.h>

static t_arena	*get_stack_arena(t_allocator *alc)
{
	int	i;

	i = -1;
	while (++i < STACK_ARENAS)
	{
		if (alc->stack_arenas[i].id == 0)
		{
			alc->stack_arenas[i].id = alc->next_arena_id++;
			return (&alc->stack_arenas[i]);
		}
	}
	return (NULL);
}

t_arena	*allocator_arena_new(t_allocator *alc)
{
	t_arena	*arena;

	arena = get_stack_arena(alc);
	if (arena)
		return (arena);
	arena = allocator_arena_create(alc);
	if (!arena)
		return (0);
	arena->id = alc->next_arena_id++;
	arena->used = 0;
	arena->next = alc->arenas;
	alc->arenas = arena;
	return (arena);
}
