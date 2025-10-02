/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:59:35 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/13 16:04:07 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator_internal.h"
#include <stdlib.h>

void	allocator_arena_destroy(t_allocator *alc, t_arena *arena)
{
	arena->id = 0;
	arena->used = 0;
	if (arena >= alc->stack_arenas && arena < alc->stack_arenas + STACK_ARENAS)
		return ;
	free(arena);
}
