/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strpncpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:37:29 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 15:59:37 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

char	*ft_stpncpy(char *dst, const char *src, size_t dsize)
{
	size_t	dlen;

	dlen = ft_strnlen(src, dsize);
	return (ft_memset(ft_mempcpy(dst, src, dlen), 0, dsize - dlen));
}
