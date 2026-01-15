/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:15:57 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/15 12:13:05 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"
#include "core/string.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>


/**
 * @brief Allocates memory using the custom allocator.
 *
 * @param size The size of memory to allocate
 * @return Pointer to the allocated memory, or NULL on failure.
 */
void	*allocator_malloc(size_t size)
{
	t_allocator	*alc;

	alc = get_allocator(NULL);
	if (size <= MAX_ALLOC_SIZE)
		return (allocator_slab_alloc(alc, size).data);
	return (malloc(size));
}

/**
 * @brief Allocates zero-initialized memory using the custom allocator.
 *
 * @param n Number of elements
 * @param size Size of each element
 * @return Pointer to the allocated memory, or NULL on failure.
 */
void	*allocator_calloc(size_t n, size_t size)
{
	void		*ptr;
	size_t		total_size;

	if (__builtin_mul_overflow(n, size, &total_size))
	{
		errno = ENOMEM;
		return (NULL);
	}
	ptr = allocator_malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}

__attribute__((__always_inline__))
static inline bool	is_on_slab(t_slab_region *slab, char *ptr)
{
	return (ptr >= slab->data && ptr < slab->data + SLAB_CAPACITY);
}

/**
 * @brief Frees memory allocated by the custom allocator.
 *
 * @param ptr Pointer to the memory to free
 */
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
