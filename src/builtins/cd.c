/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:32:22 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/21 22:49:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>

#include "env/env.h"
#include "builtins/builtins.h"
#include "builtins/cd_internal.h"
#include "libft.h"
#include "libft_printf.h"

static bool	get_relative_path(char *new, const char *old, const char *path)
{
	if (ft_strlen(old) + 1 + ft_strlen(path) + 1 > PATH_MAX)
		return (false);
	ft_strlcpy(new, old, PATH_MAX);
	if (new[ft_strlen(new) - 1] != '/')
		ft_strlcat(new, "/", PATH_MAX);
	ft_strlcat(new, path, PATH_MAX);
	return (true);
}

static int	resolve_pwd(t_env *env, char *new, const char *old, char **argv)
{
	const char	*ptr = NULL;

	if (!argv[1])
	{
		ptr = env_get(env, "HOME");
		if (!ptr || !*ptr)
			return (builtin_error(ctx(argv[0], NULL), ERR_NO_HOME, 1));
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		ptr = env_get(env, "OLDPWD");
		if (!ptr || !*ptr)
			return (builtin_error(ctx(argv[0], NULL), ERR_NO_OLDPWD, 1));
	}
	else if (argv[1][0] == '/')
		ptr = argv[1];
	else
	{
		if (!get_relative_path(new, old, argv[1]))
			return (builtin_error(ctx(argv[0], ptr), ERR_TOO_LONG, 1));
		return (0);
	}
	if (ft_strlcpy(new, ptr, PATH_MAX) > PATH_MAX)
		return (builtin_error(ctx(argv[0], ptr), ERR_TOO_LONG, 1));
	return (0);
}

int	builtin_cd(t_shell *sh, int argc, char **argv, char **envp)
{
	static char	oldpwd[PATH_MAX];
	static char	newpwd[PATH_MAX];
	char		oldbuf[PATH_MAX];
	char		newbuf[PATH_MAX];
	int			status;

	(void)envp;
	(void)argc;
	if (argv[1] && argv[2])
		return (builtin_error(ctx(argv[0], NULL), ERR_TOO_MANY_ARGS, 2));
	if (!getcwd(oldbuf, PATH_MAX))
		return (builtin_error(ctx(argv[0], NULL), ERR_PERROR, 1));
	status = resolve_pwd(&sh->env, newbuf, oldbuf, argv);
	if (status)
		return (status);
	normalize_path(newbuf);
	if (chdir(newbuf) != 0)
		return (builtin_error(ctx(argv[0], argv[1]), ERR_PERROR, 1));
	ft_strlcpy(oldpwd, oldbuf, PATH_MAX);
	ft_strlcpy(newpwd, newbuf, PATH_MAX);
	env_set(&sh->env, "OLDPWD", oldpwd, ENV_FLAG_EXPORT);
	env_set(&sh->env, "PWD", newpwd, ENV_FLAG_EXPORT);
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
		ft_printf("%s\n", newpwd);
	return (0);
}
