/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slab.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:03:27 by smamalig          #+#    #+#             */
/*   Updated: 2025/08/28 12:35:10 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator.h"
#include <stdlib.h>

// TODO: replace malloc with a custom call
t_slab_region	*allocator_slab_new(t_allocator *alc, size_t block_size,
	size_t num_blocks)
{
	t_slab_region	*next;
	t_slab_region	*new;

	next = alc->slabs;
	new = malloc(sizeof(t_slab_region));
	if (!new)
		return (NULL);
	new->next = next;
	new->capacity = num_blocks;
	new->block_size = block_size;
	alc->slabs = new;
	return (new);
}
