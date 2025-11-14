/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:34:21 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/14 12:31:32 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "builtins/builtins.h"
#include "libft.h"

static char	*find_exec(const char *arg, char **envp)
{
	static char	path[PATH_MAX];
	const char	*env_path;
	size_t		len;

	if (!arg)
		return (NULL);
	while (*envp && ft_strncmp("PATH=", *envp, 5) != 0)
		envp++;
	if (!*envp)
		return (NULL);
	env_path = *envp + 5;
	while (ft_strchr(env_path, ':'))
	{
		len = ft_strcspn(env_path, ":");
		ft_snprintf(path, PATH_MAX, "%.*s/%s", (int)len, env_path, arg);
		if (access(path, F_OK) == 0)
			return (path);
		env_path += len + 1;
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
		path = find_exec(argv[1], envp);
		if (!path)
			builtin_error(ctx("exec", argv[1]), ERR_404, 127);
		else if (access(path, X_OK) == -1 || execve(path, argv + 1, envp) == -1)
			builtin_error(ctx("exec", argv[1]), ERR_NO_PERM, 126);
	}
	return (0);
}
