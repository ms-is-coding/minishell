/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:32:22 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/03 18:21:23 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "libft_printf.h"
#include <unistd.h>

static bool	get_path(t_environ *env, char *arg, char **path)
{
	if (!arg)
		*path = get_env_path(env, "HOME");
	else if (ft_strcmp(arg, "-") == 0)
		*path = get_env_path(env, "OLDPWD");
	else
		*path = arg;
	if (!*path)
	{
		if (!arg)
			ft_dprintf(2, "cd: HOME not set\n");
		else
			ft_dprintf(2, "cd: OLDPWD not set\n");
		return (false);
	}
	return (true);
}

static void	normalize_path(char *path)
{
	char	*seg[PATH_MAX];
	char	tmp[PATH_MAX];
	char	*token;
	int		top;
	int		i;

	ft_memcpy(tmp, path, PATH_MAX);
	top = 0;
	token = ft_strtok(tmp, "/");
	while (token)
	{
		if (ft_strcmp(token, "..") == 0 && top > 0)
			top--;
		else if (ft_strcmp(token, ".") != 0)
			seg[top++] = token;
		token = ft_strtok(NULL, "/");
	}
	path[0] = '\0';
	i = 0;
	if (top == 0)
		ft_strlcpy(path, "/", PATH_MAX);
	while (i < top)
	{
    ft_strlcat(path, "/", PATH_MAX);
    ft_strlcat(path, seg[i++], PATH_MAX);
	}
}

static bool	resolve_path(char *newpwd, const char *oldpwd, const char *path)
{
	if (path[0] == '/')
		ft_strlcpy(newpwd, path, PATH_MAX);
	else if (ft_snprintf(newpwd, PATH_MAX, "%s/%s", oldpwd, path) >= PATH_MAX)
	{
		ft_dprintf(2, "cd: path too long\n");
		return (false);
	}
	normalize_path(newpwd);
	return (true);
}

int	builtin_cd(t_shell *sh, int argc, char **argv)
{
	char		*path;
	char		oldpwd[PATH_MAX];
	char		newpwd[PATH_MAX];

	(void)argc;
	argv++;
	if (argv[0] && argv[1])
		return (ft_dprintf(2, "cd: too many arguments"), 2);
	ft_strlcpy(oldpwd, get_env_path(&sh->env, "PWD" ), PATH_MAX);
	if (!oldpwd[0])
	{
		if (getcwd(oldpwd, PATH_MAX) == NULL)
			return (ft_dprintf(2, "cd: %m\n"), 1);
	}
	if (!get_path(&sh->env, argv[0], &path))
		return (1);
	if (!resolve_path(newpwd, oldpwd, path))
		return (1);
	if (chdir(newpwd) != 0)
		return (ft_dprintf(2, "cd: %m\n"), 1);
	set_env_path(&sh->env, "OLDPWD", oldpwd);
	set_env_path(&sh->env, "PWD", newpwd);
	if (argv[0] && ft_strcmp(argv[0], "-") == 0)
		ft_printf("%s\n", newpwd);
	return (0);
}
