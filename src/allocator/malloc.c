/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:15:57 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 17:31:56 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"
#include "core/string.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

void	*allocator_malloc(size_t size)
{
	t_allocator	*alc;

	alc = get_allocator(NULL);
	if (size <= MAX_ALLOC_SIZE)
		return (allocator_slab_alloc(alc, size).data);
	return (malloc(size));
}

void	*allocator_calloc(size_t n, size_t size)
{
	void		*ptr;

	if ((size != 0) && (n > SIZE_MAX / size))
	{
		errno = EOVERFLOW;
		return (NULL);
	}
	ptr = allocator_malloc(n * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, n * size);
	return (ptr);
}

__attribute__((__always_inline__))
static inline bool	is_on_slab(t_slab_region *slab, char *ptr)
{
	return (ptr >= slab->data && ptr < slab->data + SLAB_CAPACITY);
}

void	allocator_free_ptr(void *ptr)
{
	t_slab_region	*slab;
	t_allocator		*alc;
	t_allocation	alloc;

	alc = get_allocator(NULL);
	slab = alc->slabs;
	while (slab)
	{
		if (is_on_slab(slab, ptr))
		{
			alloc.data = ptr;
			alloc.region = slab;
			allocator_slab_free(alloc);
			return ;
		}
		slab = slab->next;
	}
	free(ptr);
}
