/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:32:22 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/06 12:44:29 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>

#include "env/env.h"
#include "builtins/builtins.h"
#include "builtins/cd_internal.h"
#include "libft.h"
#include "libft_printf.h"

static bool	get_current_path(t_env *env, char *cwd)
{
	const char	*ptr;

	if (!getcwd(cwd, PATH_MAX))
	{
		ptr = env_get(env, "PWD");
		if (!ptr || !*ptr)
			return (false);
		ft_strlcpy(cwd, ptr, PATH_MAX);
	}
	return (true);
}

static int	get_relative_path(char *new, const char *old, const char *path)
{
	if (ft_strlen(old) + 1 + ft_strlen(path) + 1 > PATH_MAX)
		return (builtin_error(ctx("cd", path), ERR_TOO_LONG, 1));
	ft_strlcpy(new, old, PATH_MAX);
	if (new[ft_strlen(new) - 1] != '/')
		ft_strlcat(new, "/", PATH_MAX);
	ft_strlcat(new, path, PATH_MAX);
	return (0);
}

static int	resolve_pwd(t_env *env, char *new, char *old, const char *path)
{
	const char	*ptr = NULL;

	if (!get_current_path(env, old))
		return (builtin_error(ctx("cd", NULL), ERR_PERROR, 1));
	if (!path)
	{
		ptr = env_get(env, "HOME");
		if (!ptr || !*ptr)
			return (builtin_error(ctx("cd", NULL), ERR_NO_HOME, 1));
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		ptr = env_get(env, "OLDPWD");
		if (!ptr || !*ptr)
			return (builtin_error(ctx("cd", NULL), ERR_NO_OLDPWD, 1));
	}
	else if (path[0] == '/')
		ptr = path;
	else
		return (get_relative_path(new, old, path));
	if (ft_strlcpy(new, ptr, PATH_MAX) > PATH_MAX)
		return (builtin_error(ctx("cd", ptr), ERR_TOO_LONG, 1));
	return (0);
}

static void	normalize_path(char *path)
{
	const char	*src;
	char		*dst;
	bool		is_abs;

	is_abs = false;
	if (!*path || *path == '/')
		is_abs = true;
	src = path;
	dst = path;
	while (*src)
	{
		if (*src == '/')
			collapse_slashes(&src, &dst, &path);
		else if (src[0] == '.' && (src[1] == '/' || src[1] == '\0'))
			skip_current_dir(&src);
		else if (src[0] == '.' && src[1] == '.'
			&& (src[2] == '/' || src[2] == '\0'))
			handle_parent_dir(&src, &dst, path);
		else
		{
			while (*src && *src != '/')
				*dst++ = *src++;
		}
	}
	finalize_path(path, &dst, is_abs);
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
		return (builtin_error(ctx("cd", NULL), ERR_TOO_MANY_ARGS, 2));
	status = resolve_pwd(&sh->env, newbuf, oldbuf, argv[1]);
	if (status)
		return (status);
	ft_printf("cd: changing to %s\n", newbuf);
	normalize_path(newbuf);
	ft_printf("cd: normalized to %s\n", newbuf);
	if (chdir(newbuf) != 0)
		return (builtin_error(ctx("cd", newbuf), ERR_PERROR, 1));
	ft_strlcpy(oldpwd, oldbuf, PATH_MAX);
	ft_strlcpy(newpwd, newbuf, PATH_MAX);
	env_set(&sh->env, "OLDPWD", oldpwd, ENV_FLAG_EXPORT);
	env_set(&sh->env, "PWD", newpwd, ENV_FLAG_EXPORT);
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
		ft_printf("%s\n", newpwd);
	return (0);
}
