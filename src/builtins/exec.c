/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:34:21 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 12:39:30 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft_printf.h"

static char	*find_exec(char *arg)
{
	const char	*paths[] = {
		"./", "/bin", "/usr/bin", "/usr/local/bin",
		"/sbin", "/usr/sbin", "/usr/local/sbin", NULL};
	char		*path;
	int			i;
	size_t		len;

	i = -1;
	if (!arg)
		return (NULL);
	while (paths[++i])
	{
		len = ft_strlen(paths[i]) + ft_strlen(arg) + 2;
		path = ft_malloc(len);
		if (!path)
			return (NULL);
		ft_snprintf(path, len, "%s/%s", paths[i], arg);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

int	builtin_exec(t_shell *sh, int argc, char **argv, char **envp)
{
	char	*cmd;

// todo:
// - decrement shlvl
	(void)sh;
	if (argc == 1)
		return (0);
	cmd = find_exec(argv[1]);
	if (!cmd)
		ft_printf("exec: %s: command not found\n", argv[1]);
	execve(cmd, argv + 1, envp);
	exit(0);
	return (0);
}
