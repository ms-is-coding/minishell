/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strpbrk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:35:40 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 15:57:57 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

char	*ft_strpbrk(const char *s, const char *accept)
{
	if (!s || !accept)
		return (NULL);
	while (*s)
	{
		if (ft_strchr(accept, *s))
			return ((char *)(size_t)s);
		s++;
	}
	return (NULL);
}
