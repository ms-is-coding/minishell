/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:57:35 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 13:20:55 by smamalig         ###   ########.fr       */
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
}
