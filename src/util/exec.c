/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:59:01 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 15:58:00 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "core/string.h"
#include "util/exec.h"
#include <fcntl.h>
#include <stddef.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief Reads all data from the given file descriptor until EOF.
 *
 * @param fd File descriptor to read from
 * @return Pointer to the read data buffer, or NULL on error.
 */
static char	*read_stdout(int fd)
{
	char		tmp[1024];
	char		*buf;
	char		*newbuf;
	ssize_t		n;
	size_t		len;

	n = 1;
	len = 0;
	buf = NULL;
	while (n > 0)
	{
		n = read(fd, tmp, sizeof(tmp));
		if (n == -1)
			return (ft_free(buf), NULL);
		newbuf = ft_realloc(buf, len + (size_t)n + 1);
		if (!newbuf)
			return (ft_free(buf), NULL);
		buf = newbuf;
		ft_memcpy(buf + len, tmp, (size_t)n);
		len += (size_t)n;
	}
	if (!buf)
		return (NULL);
	buf[len] = '\0';
	return (buf);
}

/**
 * @brief Redirects stderr to /dev/null.
 */
static void	close_stderr(void)
{
	int	devnull;

	devnull = open("/dev/null", O_WRONLY);
	dup2(devnull, STDERR_FILENO);
	close(devnull);
}

/**
 * @brief Executes a command and captures its standard output.
 *
 * @param argv Argument vector for the command to execute
 * @return Pointer to the captured output buffer, or NULL on error.
 */
char	*exec_with_output(char **argv)
{
	pid_t	pid;
	int		pipefd[2];
	int		stat;
	char	*buf;

	if (pipe(pipefd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close_stderr();
		execve(argv[0], argv, (char **){NULL});
		_exit(1);
	}
	close(pipefd[1]);
	buf = read_stdout(pipefd[0]);
	close(pipefd[0]);
	waitpid(pid, &stat, 0);
	return (buf);
}
