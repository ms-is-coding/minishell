/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:52:10 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/30 12:34:34 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "core/string.h"
#include <errno.h>

void	*ft_calloc(size_t n, size_t size)
{
	size_t	total;
	void	*ptr;

	if (__builtin_mul_overflow(n, size, &total))
	{
		errno = ENOMEM;
		return (NULL);
	}
	ptr = ft_malloc(total);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total);
	return (ptr);
}
