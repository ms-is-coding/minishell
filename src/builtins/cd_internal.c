/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_internal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:50:17 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/24 15:15:30 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

void	normalize_path(char *path) //needs to be separated into norminette compliant functions
{
	char	*src;
	char	*dst;
	bool	is_abs;

	is_abs = false;
	if (!*path || *path == '/')
		is_abs = true;
	src = path;
	dst = path;
	while (*src)
	{
		if (*src == '/')
		{
			if (dst == path || *(dst - 1) != '/')
				*dst++ = '/';
			while (*src == '/')
				src++;
		}
		else if (src[0] == '.' && (src[1] == '/' || src[1] == '\0'))
			src += (src[1] == '/') ? 2 : 1;
		else if (src[0] == '.' && src[1] == '.' && (src[2] == '/' || src[2] == '\0'))
		{
			src += (src[2] == '/') ? 3 : 2;
			if (dst > path && *(dst - 1) == '/')
			{
				dst--;
				while (dst > path && *(dst - 1) != '/')
					dst--;
				if (dst[0] == '.' && dst[1] == '.' && dst[2] == '/')
				{
					dst += 3;
					*dst++ = '.';
					*dst++ = '.';
					if (*src)
						*dst++ = '/';
				}
			}
			else
			{
				if (dst != path && *(dst - 1) != '/')
					*dst++ = '/';
				*dst++ = '.';
				*dst++ = '.';
				if (*src)
					*dst++ = '/';
			}
		}
		else while (*src && *src != '/')
			*dst++ = *src++;
	}
	if (dst > path + 1 && *(dst - 1) == '/')
		dst--;
	*dst = '\0';
	if (is_abs && (!path[0] || (path[0] == '.'
		&& (path[1] == '\0' || path[1] == '.'))))
	{
		path[0] = '/';
		path[1] = '\0';
	}
	if (!*path)
	{
		path[0] = '.';
		path[1] = '\0';
	}
}
