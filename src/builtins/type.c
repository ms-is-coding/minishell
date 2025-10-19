/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:42:36 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/18 18:29:21 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias/alias.h"
#include "builtins/builtins.h"
#include <stdbool.h>

static bool	try_alias(t_alias *alias, const char *cmd)
{
	const char	*exec = alias_get(alias, cmd);

	if (!exec)
		return (false);
	ft_printf("%s is aliased to '%s'\n", cmd, exec);
	return (true);
}

static bool	try_builtin(char *arg)
{
	static const char	*builtins[] = {
		"cd", "echo", "exec", "exit", "false", "true",
		":", "pwd", "env", "export", "alias", "type", NULL};
	int					i;

	i = -1;
	while (builtins[++i])
	{
		if (ft_strcmp(builtins[i], arg) == 0)
		{
			ft_printf("%s is a shell builtin\n", arg);
			return (true);
		}
	}
	return (false);
}

static bool	try_exec(char *arg)
{
	const char	*paths[] = {
		"./", "/", "/bin", "/usr/bin", "/usr/local/bin",
		"/sbin", "/usr/sbin", "/usr/local/sbin", NULL};
	char		*path;
	int			i;
	size_t		len;

	i = -1;
	while (paths[++i])
	{
		len = ft_strlen(paths[i]) + ft_strlen(arg) + 2;
		path = ft_malloc(len);
		if (!path)
			return (NULL);
		ft_snprintf(path, len, "%s/%s", paths[i], arg);
		if (access(path, X_OK) == 0)
		{
			ft_printf("%s is %s\n", arg, path);
			free(path);
			return (true);
		}
		free(path);
	}
	return (false);
}

int	builtin_type(t_shell *sh, int argc, char **argv, char **envp)
{
	int	error;

	(void)argc;
	(void)envp;
	error = 0;
	while (*(++argv))
	{
		if (try_alias(&sh->alias, *argv))
			continue ;
		if (try_builtin(*argv))
			continue ;
		if (try_exec(*argv))
			continue ;
		ft_printf("type: %s: not found\n", *argv);
		error = 1;
	}
	return (error);
}
