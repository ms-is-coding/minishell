/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:55:37 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 15:57:09 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char		*match;
	size_t		i;

	if (!haystack || !needle)
		return (NULL);
	if (!*needle)
		return ((char *)(size_t)haystack);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			match = (char *)(size_t)haystack;
			i = 1;
			while (needle[i] && needle[i] == haystack[i])
				i++;
			if (!needle[i])
				return (match);
		}
		haystack++;
	}
	return (NULL);
}
