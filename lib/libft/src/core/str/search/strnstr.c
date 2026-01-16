/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:55:37 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 15:58:08 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	char		*match;
	size_t		i;

	if (!haystack || !needle)
		return (NULL);
	if (!*needle)
		return ((char *)(size_t)haystack);
	while (*haystack && n--)
	{
		if (*haystack == *needle)
		{
			match = (char *)(size_t)haystack;
			i = 1;
			while (n-- && needle[i] && needle[i] == haystack[i])
				i++;
			if (!needle[i])
				return (match);
			n += i;
		}
		haystack++;
	}
	return (NULL);
}
