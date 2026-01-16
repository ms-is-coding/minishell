/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:25:51 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 15:57:46 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*save;

	save = NULL;
	if (!c)
		return ((char *)(size_t)s + ft_strlen(s));
	while (*s)
	{
		if (*s == (char)c)
			save = (char *)(size_t)s;
		s++;
	}
	return (save);
}
