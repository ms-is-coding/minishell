/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:42:36 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/02 14:21:30 by smamalig         ###   ########.fr       */
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
	t_builtin_fn	fn;

	fn = _builtin_find(arg);
	if (!fn)
		return (false);
	ft_printf("%s is a shell builtin\n", arg);
	return (true);
}

static bool	try_exec(char *arg, const char *env_path)
{
	char	path[PATH_MAX];
	size_t	len;

	if (!env_path)
		return (false);
	while (ft_strchr(env_path, ':'))
	{
		len = ft_strcspn(env_path, ":");
		ft_snprintf(path, PATH_MAX, "%.*s/%s", (int)len, env_path, arg);
		if (access(path, X_OK) == 0)
		{
			ft_printf("%s is %s\n", arg, path);
			return (true);
		}
		env_path += len + 1;
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
		if (try_exec(*argv, env_get(&sh->env, "PATH")))
			continue ;
		ft_dprintf(2, "type: %s: not found\n", *argv);
		error = 1;
	}
	return (error);
}
