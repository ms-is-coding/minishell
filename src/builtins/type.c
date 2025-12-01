/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:42:36 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/01 18:05:34 by mattcarniel      ###   ########.fr       */
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
		else if (opt[i] == 'P')
			*flags = (*flags | (FLAG_P | FLAG_PP)) & ~FLAG_T;
		else if (opt[i] == 'p')
			*flags = (*flags | FLAG_P) & ~FLAG_T;
		else if (opt[i] == 't')
			*flags = (*flags | FLAG_T) & ~FLAG_P;
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

static bool	try_exec(const char *arg, const char *env_path, char flags)
{
	static char	path[PATH_MAX];
	size_t		len;

	if (!arg || !env_path)
		return (false);
	while (ft_strchr(env_path, ':'))
	{
		len = ft_strcspn(env_path, ":");
		ft_snprintf(path, PATH_MAX, "%.*s/%s", (int)len, env_path, arg);
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

	argv++;
	path = env_get(&sh->env, "PATH");
	flags = set_flags(&argc, &argv);
	if (flags & FLAG_ERR)
		return (builtin_error(ctx("type", NULL), ERR_INVALID_OPT, 2));
	status = 0;
	while (*argv)
	{
		if (!(flags & FLAG_PP))
			found = try_builtin(*argv, flags);
		if (!found || (flags & (FLAG_A | FLAG_PP)))
			found |= try_exec(*argv, path, flags);
		if (!found && !(flags & (FLAG_P | FLAG_PP | FLAG_T)))
			status = builtin_error(ctx("type", *argv), ERR_404, 1);
		else if (!found)
			status = 1;
		argv++;
	}
	return (status);
}
