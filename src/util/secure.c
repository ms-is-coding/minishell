/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 23:59:58 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/24 16:26:08 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/exec.h"
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define UNREACHABLE -1

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

#if defined(__is_42sh)

# if defined(__GLIBC__) || defined(__FreeBSD__)

/**
 * @brief Executes a program securely using fexecve.
 *
 * @param path The path to the executable
 * @param argv The argument vector
 * @param envp The environment vector
 * @return This function does not return on success; on failure, it returns -1.
 */
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

# else // __GLIBC__ || __FreeBSD__

#  ifdef SYS_execveat

/**
 * @brief Executes a program securely using execveat.
 *
 * @param path The path to the executable
 * @param argv The argument vector
 * @param envp The environment vector
 * @return This function does not return on success; on failure, it returns -1.
 */
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

int	secure_execve(const char *path, char *const *argv, char *const *envp)
{
	execve(path, argv, envp);
	return (-1);
}

# endif // __GLIBC__ || __FreeBSD__

#else // __is_42sh

/**
 * @brief Fallback implementation of secure_execve that directly calls execve.
 *
 * @param path The path to the executable
 * @param argv The argument vector
 * @param envp The environment vector
 * @return This function does not return on success; on failure, it returns -1.
 */
int	secure_execve(const char *path, char *const *argv, char *const *envp)
{
	execve(path, argv, envp);
	return (-1);
}

#endif // __is_42sh
