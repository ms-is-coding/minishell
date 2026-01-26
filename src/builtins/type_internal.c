/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:41:11 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/26 16:19:57 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>
#include "builtins/type_internal.h"
#include "core/string.h"

/**
 * @brief Fills the buffer with the type of the command.
 *
 * @param buf Buffer to fill
 * @param type Type of the command
 * @return Length of the filled string.
 */
static size_t	fill_t(char *buf, char type)
{
	if (type & TYPE_EXEC)
		return (ft_strlcpy(buf, "file", 5));
	else if (type & TYPE_BUILTIN)
		return (ft_strlcpy(buf, "builtin", 8));
	else
		return (ft_strlcpy(buf, "unknown", 8));
}

/**
 * @brief Fills the buffer with the path of the command if it's executable.
 *
 * @param buf Buffer to fill
 * @param path Path of the command
 * @param type Type of the command
 * @return Length of the filled string.
 */
static size_t	fill_p(char *buf, const char *path, char type)
{
	if (!(type & TYPE_EXEC))
		return (0);
	return (ft_strlcpy(buf, path, PATH_MAX));
}

/**
 * @brief Fills the buffer with detailed information about the command.
 *
 * @param buf Buffer to fill
 * @param name Name of the command
 * @param path Path of the command
 * @param type Type of the command
 * @return Length of the filled string.
 */
static size_t	fill_e(char *buf, const char *name, const char *path, char type)
{
	ft_strlcpy(buf, name, PATH_MAX);
	if (type & TYPE_BUILTIN)
		return (ft_strlcat(buf, " is a shell builtin", PATH_MAX));
	else if (type & TYPE_EXEC)
	{
		ft_strlcat(buf, " is ", PATH_MAX);
		return (ft_strlcat(buf, path, PATH_MAX));
	}
	else
		return (ft_strlcat(buf, " is unknown", PATH_MAX));
}

/**
 * @brief Outputs type information based on the provided flags.
 *
 * @param name Name of the command
 * @param path Path of the command
 * @param type Type of the command
 * @param flags Flags indicating the output format
 */
bool	type_info(const char *name, const char *path, char type, char flags)
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
	return (true);
}
