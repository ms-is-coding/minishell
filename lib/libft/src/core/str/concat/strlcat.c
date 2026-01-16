/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:55:37 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:00:05 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	const size_t	src_sz = ft_strlen(src);
	const size_t	dst_sz = ft_strlen(dst);

	if (dsize <= dst_sz)
		return (dsize + src_sz);
	dst += dst_sz;
	while (*src && dst_sz < --dsize)
		*dst++ = *src++;
	*dst = '\0';
	return (dst_sz + src_sz);
}
