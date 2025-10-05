/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:13:50 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/03 00:43:58 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"
#include <stdlib.h>

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
