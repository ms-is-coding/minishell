/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 00:25:37 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/14 00:28:00 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator_internal.h"

t_slab_region	*allocator_slab_create(t_allocator *alc)
{
	int	i;

	i = -1;
	while (++i < STACK_SLABS)
	{
		if (alc->stack_slabs[i].id == 0)
			return (&alc->stack_slabs[i]);
	}
	return (allocator_alloc(alc, sizeof(t_slab_region), NULL).data);
}
