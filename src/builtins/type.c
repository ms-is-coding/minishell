/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:42:36 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/20 11:42:21 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include "builtins/builtins.h"
#include "builtins/type_internal.h"

static bool	get_flags(const char *opt, char *flags)
{
	int		i;

	if (!opt || opt[0] != '-' || ft_strcmp(opt, "-") == 0)
		return (false);
	i = 1;
	while (opt[i])
	{
		if (opt[i] == 'a')
			*flags |= FLAG_A;
		else if (opt[i] == 'p')
			*flags |= FLAG_P;
		else if (opt[i] == 'P')
			*flags |= FLAG_PP;
		else if (opt[i] == 't')
			*flags |= FLAG_T;
		else
		{
			*flags = FLAG_ERR;
			return (false);
		}
		i++;
	}
	return (true);
}

static char	set_flags(int *argc, char ***argv)
{
	char	flags;

	if (*argc < 2)
		return (0);
	flags = 0;
	while (*argc > 1)
	{
		if (ft_strcmp(**argv, "--") == 0)
		{
			*argc -= 1;
			*argv += 1;
			break ;
		}
		if (!get_flags(**argv, &flags))
			break ;
		*argc -= 1;
		*argv += 1;
	}
	return (flags);
}

static bool	try_builtin(char *name, char flags)
{
	t_builtin_fn	fn;

	fn = _builtin_find(name);
	if (!fn)
		return (false);
	type_info(name, NULL, TYPE_BUILTIN, flags);
	return (true);
}

static bool	try_exec(char *arg, const char *env_path, char flags)
{
	char	path[PATH_MAX];
	size_t	len;

	if (!env_path)
		return (false);
	while (ft_strchr(env_path, ':'))
	{
		len = ft_strcspn(env_path, ":"); //if path_max is smaller, big issue
		ft_strlcpy(path, env_path, len + 1);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, arg, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			type_info(arg, path, TYPE_EXEC, flags);
			return (true);
		}
		env_path += len + 1;
	}
	return (false);
}

int	builtin_type(
	t_shell *sh,
	__attribute__((unused)) int argc,
	char **argv,
	__attribute__((unused)) char **envp)
{
	const char	*path;
	int			status;
	char		flags;
	bool		found;

	path = env_get(&sh->env, "PATH");
	argv++;
	flags = set_flags(&argc, &argv);
	status = 0;
	while (*argv)
	{
		found = try_builtin(*argv, flags);
		if (!found || (flags & (FLAG_A | FLAG_PP)))
			found |= try_exec(*argv, path, flags);
		if (!found)
		{
			if (!(flags & (FLAG_P | FLAG_PP | FLAG_T)))
				status = builtin_error(ctx("type", *argv), ERR_404, 1);
			else
				status = 1;
		}
		argv++;
	}
	return (status);
}
