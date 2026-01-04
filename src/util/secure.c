/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 23:59:58 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 12:21:18 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/exec.h"
#include "util/help.h"
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define UNREACHABLE -1

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

#if defined(__is_42sh)

# if defined(__GLIBC__) || defined (__APPLE__) || defined(__FreeBSD__)

int	secure_execve(const char *path, char *const *argv, char *const *envp)
{
	int	fd;

	fd = secure_open(path, O_RDONLY | O_NOFOLLOW | O_CLOEXEC);
	if (fd == -1)
		return (-1);
	if (fexecve(fd, argv, envp) == -1)
	{
		close(fd);
		return (-1);
	}
	__builtin_unreachable();
}

# else // __GLIBC__ || __APPLE__ || __FreeBSD__

#  ifdef SYS_execveat

int	secure_execve(const char *path, char *const *argv, char *const *envp)
{
	int	fd;

	fd = secure_open(path, O_RDONLY | O_NOFOLLOW | O_CLOEXEC);
	if (fd == -1)
		return (-1);
	if (execveat(fd, "", argv, envp, AT_EMPTY_PATH) == -1)
	{
		close(fd);
		return (-1);
	}
	__builtin_unreachable();
}
#  endif

#  error "Secure execve is not available"

# endif // __GLIBC__ || __APPLE__ || __FreeBSD__

#else // __is_42sh

int	secure_execve(const char *path, char *const *argv, char *const *envp)
{
	execve(path, argv, envp);
	return (-1);
}

#endif // __is_42sh
