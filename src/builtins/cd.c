/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:44:16 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/12/01 19:14:21 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

#include "env/env.h"
#include "builtins/builtins.h"
#include "libft.h"
#include "allocator/allocator.h"

static const char	*resolve_cwd(t_env *env, const char *path)
{
	const char	*ptr;

	ptr = path;
	if (!path)
	{
		ptr = env_get(env, "HOME");
		if (!ptr)
			builtin_error(ctx("cd", NULL), ERR_NO_HOME, 1);
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		ptr = env_get(env, "OLDPWD");
		if (!ptr)
			builtin_error(ctx("cd", NULL), ERR_NO_OLDPWD, 1);
	}
	if (chdir(ptr))
	{
		builtin_error(ctx("cd", path), ERR_PERROR, 1);
		return (NULL);
	}
	return (ptr);
}

static void	free_pwds(char **old, char **new)
{
	if (*old)
		allocator_free_ptr(*old);
	if (*new)
		allocator_free_ptr(*new);
}

static int	get_pwds(t_shell *sh, const char *cwd, char **old, char **new)
{
	const char	*ptr;

	if (!getcwd(*new, PATH_MAX))
	{
		if (ft_strcmp(cwd, "..") == 0)
			return (builtin_error(ctx("cd", cwd), ERR_PREV_DIR, 1));
		if (ft_strcmp(cwd, ".") == 0)
			return (builtin_error(ctx("cd", cwd), ERR_CURR_DIR, 1));
		return (builtin_error(ctx("cd", cwd), ERR_PERROR, 1));
	}
	ptr = env_get(&sh->env, "PWD");
	if (!ptr)
		ft_strlcpy(*old, "", PATH_MAX);
	else
		ft_strlcpy(*old, ptr, PATH_MAX);
	return (0);
}

static int	set_pwds(t_shell *sh, const char *old, const char *new)
{
	if (env_set(&sh->env, "OLDPWD", old, ENV_FLAG_EXPORT | ENV_FLAG_STACK_KEY))
		return (builtin_error(ctx("cd", "OLDPWD"), ERR_BAD_SET, 1));
	if (env_set(&sh->env, "PWD", new, ENV_FLAG_EXPORT | ENV_FLAG_STACK_KEY))
		return (builtin_error(ctx("cd", "PWD"), ERR_BAD_SET, 1));
	return (0);
}

int	builtin_cd(
	t_shell *sh,
	int argc,
	char **argv,
	__attribute__((unused)) char **envp)
{
	const char	*cwd;
	char		*old;
	char		*new;

	if (argc > 2)
		return (builtin_error(ctx("cd", NULL), ERR_TOO_MANY_ARGS, 2));
	cwd = resolve_cwd(&sh->env, argv[1]);
	if (!cwd)
		return (1);
	new = allocator_calloc(PATH_MAX, sizeof(char));
	old = allocator_calloc(PATH_MAX, sizeof(char));
	if (!new || !old)
	{
		free_pwds(&old, &new);
		return (builtin_error(ctx("cd", NULL), ERR_ALLOC, 1));
	}
	if (get_pwds(sh, cwd, &old, &new))
		return (free_pwds(&old, &new), 1);
	if (set_pwds(sh, old, new))
		return (free_pwds(&old, &new), 1);
	if (argc == 2 && ft_strcmp(argv[1], "-") == 0)
		ft_printf("%s\n", new);
	return (0);
}
