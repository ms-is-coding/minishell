/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:29:20 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/13 18:47:38 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator_internal.h"
#include <stdlib.h>

void	allocator_slab_destroy(t_allocator *alc, t_slab_region *slab)
{
	slab->id = 0;
	slab->used = 0;
	if (slab >= alc->stack_slabs && slab < alc->stack_slabs + STACK_SLABS)
		return ;
	free(slab);
}
