/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:28:45 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 13:17:32 by smamalig         ###   ########.fr       */
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
}
