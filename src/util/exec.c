/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:59:01 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/18 20:00:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "util/exec.h"
#include <fcntl.h>
#include <stddef.h>
#include <sys/wait.h>
#include <unistd.h>

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

char	*exec_with_output(char **argv)
{
	pid_t	pid;
	int		pipefd[2];
	int		stat;
	char	*buf;

	buf = NULL;
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
		execve(argv[0], argv, (char **){NULL});
		_exit(1);
	}
	close(pipefd[1]);
	buf = read_stdout(pipefd[0]);
	close(pipefd[0]);
	waitpid(pid, &stat, 0);
	return (buf);
}
