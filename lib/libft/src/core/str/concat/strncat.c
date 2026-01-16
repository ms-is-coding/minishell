/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:11:25 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:00:10 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

char	*ft_strncat(char *dst, const char *src, size_t ssize)
{
	char	*cpy;

	cpy = dst;
	while (*dst)
		dst++;
	while (ssize-- > 0 && *src)
		*dst++ = *src++;
	*dst = 0;
	return (cpy);
}
