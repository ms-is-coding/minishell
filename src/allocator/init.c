/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:57:35 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/16 17:11:41 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include <stdint.h>

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
}
