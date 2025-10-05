/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:43:29 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/03 00:43:22 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"

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
