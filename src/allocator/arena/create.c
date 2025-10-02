/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:04:43 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/13 18:21:20 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"

// this function assumes allocator_alloc will fallback to malloc
t_arena	*allocator_arena_create(t_allocator *alc)
{
	int	i;

	i = -1;
	while (++i < STACK_ARENAS)
	{
		if (alc->stack_arenas[i].id == 0)
			return (&alc->stack_arenas[i]);
	}
	return (allocator_alloc(alc, sizeof(t_arena), NULL).data);
}
