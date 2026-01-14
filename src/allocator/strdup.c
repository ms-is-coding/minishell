/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:38:28 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:27:31 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "core/string.h"

/**
 * @brief Duplicates a string using the custom allocator.
 *
 * @param s The string to duplicate
 * @return Pointer to the duplicated string, or NULL on failure.
 */
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

/**
 * @brief Duplicates up to n characters of a string using the custom allocator.
 *
 * @param s The string to duplicate
 * @param n The maximum number of characters to duplicate
 * @return Pointer to the duplicated string, or NULL on failure.
 */
char	*allocator_strndup(const char *s, const size_t n)
{
	char	*res;

	res = allocator_malloc(sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	((char *)ft_mempcpy(res, s, n))[0] = 0;
	return (res);
}
