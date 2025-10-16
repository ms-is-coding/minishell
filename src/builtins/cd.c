/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:32:22 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/16 16:52:32 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "env/env.h"
#include "builtins.h"
#include "libft.h"
#include "libft_printf.h"

static void normalize_path(char *path)
{
	char	*src;
	char	*dst;
	bool	is_abs;

	is_abs = false;
	if (!*path || *path == '/')
		is_abs = true;
	src = path;
	dst = path;
	while (*src)
	{
		if (*src == '/')
		{
			*dst++ = '/';
			while (*src == '/')
				src++;
		}
		else if (src[0] == '.' && (src[1] == '/' || src[1] == '\0'))
			src += (src[1] == '/') ? 2 : 1;
		else if (src[0] == '.' && src[1] == '.' && (src[2] == '/' || src[2] == '\0'))
		{
			src += (src[2] == '/') ? 3 : 2;
			if (dst > path && *(dst - 1) == '/')
			{
				dst--;
				while (dst > path && *(dst - 1) != '/')
					dst--;
				if (dst[0] == '.' && dst[1] == '.' && dst[2] == '/')
				{
					dst += 3;
					*dst++ = '.';
					*dst++ = '.';
					if (*src)
						*dst++ = '/';
				}
			}
			else
			{
				if (dst != path && *(dst - 1) != '/')
					*dst++ = '/';
				*dst++ = '.';
				*dst++ = '.';
				if (*src)
					*dst++ = '/';
			}
		}
		else while (*src && *src != '/')
			*dst++ = *src++;
	}
	if (dst > path + 1 && *(dst - 1) == '/')
		dst--;
	*dst = '\0';
	if (is_abs && (!path[0] || (path[0] == '.'
		&& (path[1] == '\0' || (path[1] == '.' && path[2] == '\0')))))
	{
		path[0] = '/';
		path[1] = '\0';
	}
	if (!*path)
	{
		path[0] = '.';
		path[1] = '\0';
	}
}

static t_error	resolve_pwd(t_env *env, char *newpwd, char *oldpwd, const char *path)
{
	if (!getcwd(oldpwd, PATH_MAX))
		return (ERR_UNKNOWN);
	if (!path)
	{
		if (!ft_strlcpy(newpwd, env_get(env, "HOME"), PATH_MAX))
			return (ERR_UNKNOWN);
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		if (!ft_strlcpy(newpwd, env_get(env, "OLDPWD"), PATH_MAX))
			return (ERR_UNKNOWN);
		ft_printf("%s\n", newpwd);
	}
	else if (path[0] == '/')
		ft_strlcpy(newpwd, path, PATH_MAX);
	else
	{
		if (ft_strlen(oldpwd) + 1 + ft_strlen(path) + 1 > PATH_MAX)
			return (ERR_UNKNOWN);
		ft_strlcpy(newpwd, oldpwd, PATH_MAX);
		if (newpwd[ft_strlen(newpwd) - 1] != '/')
			ft_strlcat(newpwd, "/", PATH_MAX);
		ft_strlcat(newpwd, path, PATH_MAX);
	}
	return (ERR_NONE);
}

int	builtin_cd(t_shell *sh, int argc, char **argv, char **envp)
{
	char		oldpwd[PATH_MAX];
	char		newpwd[PATH_MAX];

	(void)envp;
	(void)argc;
	if (argv[1] && argv[2])
		return (builtin_error(ctx(argv[0], NULL), ERR_TOO_MANY_ARGS, 2));
	newpwd[0] = '\0'; //memset ?
	oldpwd[0] = '\0';
	resolve_pwd(&sh->env, newpwd, oldpwd, argv[1]);
	ft_printf("cd from: %s\n", oldpwd); //debug
	ft_printf("cd to: %s\n", newpwd); //debug
	if (chdir(newpwd) != 0)
		return (builtin_error(ctx(argv[0], argv[1]), ERR_PERROR, 1));
	normalize_path(newpwd);
	env_set(&sh->env, "OLDPWD", oldpwd, true);
	env_set(&sh->env, "PWD", newpwd, true);
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
		ft_printf("%s\n", newpwd); //necessary ?
	return (0);
}
