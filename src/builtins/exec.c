/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:34:21 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 19:51:57 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "builtins/builtins.h"
#include "core/string.h"
#include "core/stdio.h"

static const char	*find_env_path(char **envp)
{
	const char	*env_path;

	while (*envp && ft_strncmp("PATH=", *envp, 5) != 0)
		envp++;
	if (!*envp)
		return (NULL);
	env_path = *envp + 5;
	return (env_path);
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
	if (!argv[0])
		return (0);
	if (ft_strchr(argv[0], '/'))
	{
		if (access(argv[0], F_OK) == -1)
			builtin_error(ctx("exec", argv[0]), ERR_404, 127);
		else if (access(argv[0], X_OK) == -1
			|| execve(argv[0], argv, envp) == -1)
			builtin_error(ctx("exec", argv[0]), ERR_NO_PERM, 126);
	}
	else
	{
		path = find_exec(argv[0], find_env_path(envp));
		if (!path)
			builtin_error(ctx("exec", argv[0]), ERR_404, 127);
		else if (access(path, X_OK) == -1 || execve(path, argv, envp) == -1)
			builtin_error(ctx("exec", argv[0]), ERR_NO_PERM, 126);
	}
	return (0);
}
