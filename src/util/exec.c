/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:59:01 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/18 19:37:15 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/exec.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	open_stdout(void)
{
	int	fd;

	fd = open("/tmp/.trash_stdout", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	return (0);
}

static char	*read_stdout(void)
{
	static char	buffer[1024];
	ssize_t		read_size;
	int			fd;

	fd = open("/tmp/.trash_stdout", O_RDONLY);
	if (fd == -1)
		return (NULL);
	read_size = read(fd, buffer, sizeof(buffer));
	close(fd);
	if (read_size == -1 || read_size == sizeof(buffer))
		return (NULL);
	buffer[read_size] = '\0';
	return (buffer);
}

char	*exec_with_output(char **argv)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		close(0);
		if (open_stdout() == -1)
			exit(1);
		execve(argv[0], argv, (char **){NULL});
		exit(1);
	}
	else
		waitpid(pid, &stat, 0);
	return (read_stdout());
}
