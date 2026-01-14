/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:28:45 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:26:46 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"

/**
 * @brief Destroys the allocator and frees all associated memory.
 *
 * @param alc Pointer to the allocator to destroy
 */
void	allocator_destroy(t_allocator *alc)
{
	void	*temp;

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
