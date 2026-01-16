/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:37:58 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:17:08 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "core/string.h"
#include <errno.h>

static inline size_t	ft_ptr_size(void *ptr)
{
	return (((size_t *)ptr)[-1]);
}

// see `man 3p realloc`
void	*ft_realloc(void *ptr, size_t size)
{
	size_t	old_size;
	void	*alloc;

	if (!ptr)
		return (ft_malloc(size));
	if (size == 0)
	{
		ft_free(ptr);
		errno = ENOMEM;
		return (NULL);
	}
	old_size = ft_ptr_size(ptr);
	if (size <= old_size)
		return (ptr);
	alloc = ft_malloc(size);
	if (!alloc)
		return (NULL);
	ft_mempcpy(alloc, ptr, old_size);
	ft_free(ptr);
	return (alloc);
}
