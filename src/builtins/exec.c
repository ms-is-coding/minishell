/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:34:21 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/05 13:11:24 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "builtins/builtins.h"
#include "libft.h"

static char	**get_paths(char **envp)
{
	int		i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

static char	*find_cmd_path(char *cmd, char **envp)
{
	char		**paths;
	char		*path;
	int			i;
	size_t		len;

	i = 0;
	if (!cmd)
		return (NULL);
	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		len = ft_strlen(paths[i]) + ft_strlen(cmd) + 2;
		path = allocator_malloc(sizeof(char) * len);
		if (!path)
			return (NULL);
		ft_strlcpy(path, paths[i++], len);
		ft_strlcat(path, "/", len);
		ft_strlcat(path, cmd, len);
		if (access(path, F_OK) == 0)
			return (path);
		allocator_free(path);
	}
	return (NULL);
}

int	builtin_exec(t_shell *sh, int argc, char **argv, char **envp)
{
	char	*path;

	(void)sh;
	(void)argc;
	if (!*(argv + 1))
		return (0);
	if (ft_strchr(argv[1], '/'))
	{
		if (access(argv[1], F_OK) == -1)
			builtin_error(ctx("exec", argv[1]), ERR_404, 127);
		else if (access(argv[1], X_OK) == -1
			|| execve(argv[1], argv + 1, envp) == -1)
			builtin_error(ctx("exec", argv[1]), ERR_NO_PERM, 126);
	}
	else
	{
		path = find_cmd_path(argv[1], envp);
		if (!path)
			builtin_error(ctx("exec", argv[1]), ERR_404, 127);
		else if (access(path, X_OK) == -1 || execve(path, argv + 1, envp) == -1)
			builtin_error(ctx("exec", argv[1]), ERR_NO_PERM, 126);
		allocator_free(path);
	}
	return (0);
}
