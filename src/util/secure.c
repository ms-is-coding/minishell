/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 23:59:58 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 14:20:13 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/exec.h"
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Opens a file securely, ensuring it is a regular file.
 *
 * @param file The path to the file to open
 * @param oflag The flags to use when opening the file
 * @return The file descriptor on success, or -1 on failure.
 */
int	secure_open(const char *file, int oflag)
{
	int			fd;
	struct stat	st;

	fd = open(file, oflag);
	if (fd == -1)
		return (-1);
	if (fstat(fd, &st) != 0)
	{
		close(fd);
		return (-1);
	}
	if (!S_ISREG(st.st_mode))
	{
		close(fd);
		errno = EINVAL;
		return (-1);
	}
	return (fd);
}
