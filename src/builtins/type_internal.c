/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:41:11 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/12/01 17:59:45 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "builtins/type_internal.h"
#include "builtins/builtins.h"
#include "libft.h"

static size_t	fill_t(char *buf, char type)
{
	if (type & TYPE_EXEC)
		return (ft_strlcpy(buf, "file", 5));
	else if (type & TYPE_BUILTIN)
		return (ft_strlcpy(buf, "builtin", 8));
	else
		return (ft_strlcpy(buf, "unknown", 8));
}

static size_t	fill_p(char *buf, const char *path, char type)
{
	if (!(type & TYPE_EXEC))
		return (0);
	return (ft_strlcpy(buf, path, PATH_MAX));
}

static size_t	fill_e(char *buf, const char *name, const char *path, char type)
{
	ft_strlcpy(buf, name, PATH_MAX);
	if (type & TYPE_BUILTIN)
		return (ft_strlcat(buf, " is a builtin", PATH_MAX));
	else if (type & TYPE_EXEC)
	{
		ft_strlcat(buf, " is ", PATH_MAX);
		return (ft_strlcat(buf, path, PATH_MAX));
	}
	else
		return (ft_strlcat(buf, " is unknown", PATH_MAX));
}

void	type_info(const char *name, const char *path, char type, char flags)
{
	char	buf[PATH_MAX];
	size_t	len;

	if (flags & FLAG_T)
		len = fill_t(buf, type);
	else if (flags & FLAG_P)
		len = fill_p(buf, path, type);
	else
		len = fill_e(buf, name, path, type);
	buf[len] = '\n';
	write(STDOUT_FILENO, buf, len + 1);
	ft_memset(buf, 0, PATH_MAX);
}
