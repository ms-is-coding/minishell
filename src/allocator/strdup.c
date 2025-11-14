/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:38:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/14 12:47:28 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "libft.h"

char	*allocator_strdup(const char *s)
{
	char		*res;
	size_t		len;

	len = ft_strlen(s);
	res = allocator_malloc(len + 1);
	if (!res)
		return (NULL);
	((char *)ft_mempcpy(res, s, len))[0] = 0;
	return (res);
}

char	*allocator_strndup(const char *s, const size_t n)
{
	char	*res;

	res = allocator_malloc(sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	((char *)ft_mempcpy(res, s, n))[0] = 0;
	return (res);
}
