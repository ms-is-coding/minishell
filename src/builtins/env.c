/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:53:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/18 18:06:52 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include "builtins/builtins.h"
#include "libft.h"

static int	env_exec(t_shell *sh, int argc, char **argv, char **envp)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (builtin_error(ctx("env", NULL), ERR_PERROR, 1));
	if (pid == 0)
		return (builtin_exec(sh, argc, argv, envp));
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

static int	env_print(char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	while (envp && envp[i])
	{
		len = ft_strlen(envp[i]);
		envp[i][len] = '\n';
		write(STDOUT_FILENO, envp[i], len + 1);
		envp[i][len] = '\0';
		i++;
	}
	return (0);
}

int	builtin_env(
	__attribute__((unused)) t_shell *sh,
	int argc,
	__attribute__((unused)) char **argv,
	__attribute__((unused)) char **envp)
{
	if (argc > 1)
		return (env_exec(sh, argc, argv, envp));
	else
		return (env_print(envp));
}
