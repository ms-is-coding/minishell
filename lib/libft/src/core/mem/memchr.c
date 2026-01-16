/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:32:01 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:01:13 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_ = s;

	while (n--)
	{
		if (*s_ == (unsigned char)c)
			return ((void *)(size_t)s_);
		s_++;
	}
	return (NULL);
}
