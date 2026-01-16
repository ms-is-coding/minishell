/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:38:41 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:01:17 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_ = s1;
	const unsigned char	*s2_ = s2;

	while (n--)
	{
		if (*s1_ != *s2_)
			return (*s1_ - *s2_);
		s1_++;
		s2_++;
	}
	return (0);
}
