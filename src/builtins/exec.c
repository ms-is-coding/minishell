/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:34:21 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 17:24:01 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "builtins/builtins.h"
#include "core/string.h"
#include "core/stdio.h"

/**
 * @brief Finds the executable path for a given command argument.
 *
 * @param arg Command argument (executable name)
 * @param envp Environment variables
 * @return Path to the executable if found, NULL otherwise.
 */
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

/**
 * @brief Executes a command, replacing the current process image.
 *
 * @param sh Pointer to the shell structure (unused)
 * @param argc Argument count (unused)
 * @param argv Argument vector
 * @param envp Environment variables
 * @return Exit code of the execution.
 */
int	builtin_exec(
	__attribute__((unused)) t_shell *sh,
	__attribute__((unused)) int argc,
	char **argv,
	char **envp)
{
	char	*path;

	argv++;
	if (!*argv)
		return (0);
	if (ft_strchr(*argv, '/'))
	{
		if (access(*argv, F_OK) == -1)
			builtin_error(ctx("exec", *argv), ERR_404, 127);
		else if (access(argv[1], X_OK) == -1
			|| execve(argv[1], argv + 1, envp) == -1)
			builtin_error(ctx("exec", *argv), ERR_NO_PERM, 126);
	}
	else
	{
		path = find_exec(*argv, envp);
		if (!path)
			builtin_error(ctx("exec", *argv), ERR_404, 127);
		else if (access(path, X_OK) == -1 || execve(path, argv, envp) == -1)
			builtin_error(ctx("exec", *argv), ERR_NO_PERM, 126);
	}
	return (0);
}
