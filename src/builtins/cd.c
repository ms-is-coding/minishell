/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:32:22 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 13:40:42 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "env/env.h"
#include "builtins.h"
#include "libft.h"
#include "libft_printf.h"

static bool	get_path(t_env *env, char *arg, char **path)
{
	if (!arg)
		*path = env_get(env, "HOME");
	else if (ft_strcmp(arg, "-") == 0)
		*path = env_get(env, "OLDPWD");
	else
		*path = arg;
	if (!*path)
		return (false);
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
		return (false);
	normalize_path(newpwd);
	return (true);
}

int	builtin_cd(t_shell *sh, int argc, char **argv, char **envp)
{
	char		*path;
	char		oldpwd[PATH_MAX];
	char		newpwd[PATH_MAX];

	(void)envp;
	(void)argc;
	if (argv[1] && argv[2])
		return (2); //too many args
	ft_strlcpy(oldpwd, env_get(&sh->env, "PWD"), PATH_MAX);
	if (!oldpwd[0])
	{
		if (getcwd(oldpwd, PATH_MAX) == NULL)
			return (1); //perror
	}
	if (!get_path(&sh->env, argv[1], &path))
		return (1); //HOME or OLDPWD not set
	if (!resolve_path(newpwd, oldpwd, path))
		return (1); //path too long
	if (chdir(newpwd) != 0)
		return (ft_dprintf(2, "cd: %m\n"), 1);
	env_set(&sh->env, "OLDPWD", oldpwd, true);
	env_set(&sh->env, "PWD", newpwd, true);
	if (argv[0] && ft_strcmp(argv[0], "-") == 0)
		ft_printf("%s\n", newpwd);
	return (0);
}
