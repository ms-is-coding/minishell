/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_internal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:50:17 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/11/05 13:13:54 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

void	collapse_slashes(const char **src, char **dst, char **path)
{
	if (**src == '/')
	{
		if (*dst == *path || *(*dst - 1) != '/')
			*(*dst)++ = '/';
		while (**src == '/')
			(*src)++;
	}
}

void	skip_current_dir(const char **src)
{
	if ((*src)[0] == '.' && ((*src)[1] == '/' || (*src)[1] == '\0'))
	{
		if ((*src)[1] == '/')
			*src += 2;
		else
			*src += 1;
	}
}

void	rollback_dir(const char *src, char **dst, char *path)
{
	if (*dst > path && *(*dst - 1) == '/')
	{
		(*dst)--;
		while (*dst > path && *(*dst - 1) != '/')
			(*dst)--;
		if ((*dst)[0] == '.' && (*dst)[1] == '.' && (*dst)[2] == '/')
		{
			*dst += 3;
			*(*dst)++ = '.';
			*(*dst)++ = '.';
			if (*src)
				*(*dst)++ = '/';
		}
	}
	else
	{
		if (*dst != path && *(*dst - 1) != '/')
			*(*dst++) = '/';
		*(*dst)++ = '.';
		*(*dst)++ = '.';
		if (*src)
			*(*dst)++ = '/';
	}
}

void	handle_parent_dir(const char **src, char **dst, char *path)
{
	if ((*src)[2] == '/')
		*src += 3;
	else
		*src += 2;
	rollback_dir(*src, dst, path);
}

void	finalize_path(char *path, char **dst, bool is_abs)
{
	if (*dst > path + 1 && *(*dst - 1) == '/')
		(*dst)--;
	**dst = '\0';
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
