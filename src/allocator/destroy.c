/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:28:45 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/14 02:08:28 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"

void	allocator_destroy(t_allocator *alc)
{
	void	*temp;
	int		i;

	i = -1;
	while (++i < STACK_ARENAS)
		allocator_arena_destroy(alc, &alc->stack_arenas[i]);
	while (alc->arenas)
	{
		temp = alc->arenas->next;
		allocator_arena_destroy(alc, alc->arenas);
		alc->arenas = temp;
	}
	while (alc->slabs)
	{
		temp = alc->slabs->next;
		allocator_slab_destroy(alc, alc->slabs);
		alc->slabs = temp;
	}
}
