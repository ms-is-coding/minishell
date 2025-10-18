/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:32:22 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/18 14:44:33 by mattcarniel      ###   ########.fr       */
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
			src += (src[1] == '/') ? 2 : 1;		else if (src[0] == '.' && src[1] == '.' && (src[2] == '/' || src[2] == '\0'))
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

static t_error	resolve_pwd(t_env *env, char *newbuf, const char *oldbuf, char **argv)
{
	if (!argv[1])
	{
		if (!ft_strlcpy(newbuf, env_get(env, "HOME"), PATH_MAX))
			return (builtin_error(ctx(argv[0], NULL), ERR_NO_HOME, 1));
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		if (!ft_strlcpy(newbuf, env_get(env, "OLDPWD"), PATH_MAX))
			return (builtin_error(ctx(argv[0], NULL), ERR_NO_OLDPWD, 1));
	}
	else if (argv[1][0] == '/')
	{
		if (ft_strlcpy(newbuf, argv[1], PATH_MAX) > PATH_MAX)
			return (builtin_error(ctx(argv[0], argv[1]), ERR_TOO_LONG, 1));
	}
	else
	{
		if (ft_strlen(oldbuf) + 1 + ft_strlen(argv[1]) + 1 > PATH_MAX)
			return (builtin_error(ctx(argv[0], argv[1]), ERR_TOO_LONG, 1));
		ft_strlcpy(newbuf, oldbuf, PATH_MAX);
		if (newbuf[ft_strlen(newbuf) - 1] != '/')
			ft_strlcat(newbuf, "/", PATH_MAX);
		ft_strlcat(newbuf, argv[1], PATH_MAX);
	}
	return (ERR_NONE);
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
	env_set(&sh->env, "OLDPWD", oldpwd, true);
	env_set(&sh->env, "PWD", newpwd, true);
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
		ft_printf("%s\n", newpwd);
	return (0);
}
