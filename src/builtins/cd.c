/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:44:16 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/26 15:17:50 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

#include "env/env.h"
#include "builtins/builtins.h"
#include "core/string.h"
#include "core/stdio.h"

/**
 * @brief Resolves the target directory for the cd command.
 *
 * @param env Pointer to the environment structure
 * @param path The target directory path
 * @return The resolved directory path, or NULL on error.
 */
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

/**
 * @brief Frees the allocated memory for old and new working directories.
 *
 * @param old Pointer to the old working directory
 * @param new Pointer to the new working directory
 */
static void	free_pwds(char **old, char **new)
{
	if (*old)
		ft_free(*old);
	if (*new)
		ft_free(*new);
}

/**
 * @brief Retrieves the current and previous working directories.
 *
 * @param sh Pointer to the shell structure
 * @param cwd The target directory to change to
 * @param old Pointer to store the old working directory
 * @param new Pointer to store the new working directory
 * @return True on success, false on failure.
 */
static bool	get_pwds(t_shell *sh, const char *cwd, char **old, char **new)
{
	const char	*ptr;

	if (!getcwd(*new, PATH_MAX))
	{
		if (ft_strcmp(cwd, "..") == 0)
			builtin_error(ctx("cd", cwd), ERR_PREV_DIR, 1);
		else if (ft_strcmp(cwd, ".") == 0)
			builtin_error(ctx("cd", cwd), ERR_CURR_DIR, 1);
		else
			builtin_error(ctx("cd", cwd), ERR_PERROR, 1);
		return (false);
	}
	ptr = env_get(&sh->env, "PWD");
	if (!ptr)
		ft_strlcpy(*old, "", PATH_MAX);
	else
		ft_strlcpy(*old, ptr, PATH_MAX);
	return (true);
}

/**
 * @brief Sets the OLDPWD and PWD environment variables.
 *
 * @param sh Pointer to the shell structure
 * @param old The old working directory
 * @param new The new working directory
 * @return True on success, false on failure
 */
static bool	set_pwds(t_shell *sh, const char *old, const char *new)
{
	if (env_set(&sh->env, "OLDPWD", old, ENV_FLAG_EXPORT | ENV_FLAG_STACK_KEY))
	{
		builtin_error(ctx("cd", "OLDPWD"), ERR_BAD_SET, 1);
		return (false);
	}
	if (env_set(&sh->env, "PWD", new, ENV_FLAG_EXPORT | ENV_FLAG_STACK_KEY))
	{
		builtin_error(ctx("cd", "PWD"), ERR_BAD_SET, 1);
		return (false);
	}
	return (true);
}

/**
 * @brief Changes the current working directory.
 *
 * @param sh Pointer to the shell structure
 * @param argc Argument count
 * @param argv Argument vector
 * @param envp Environment variables (unused)
 * @return Exit code of the cd command.
 */
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
	new = ft_calloc(PATH_MAX, sizeof(char));
	old = ft_calloc(PATH_MAX, sizeof(char));
	if (!new || !old)
	{
		free_pwds(&old, &new);
		return (builtin_error(ctx("cd", NULL), ERR_ALLOC, 1));
	}
	if (!get_pwds(sh, cwd, &old, &new))
		return (free_pwds(&old, &new), 1);
	if (!set_pwds(sh, old, new))
		return (free_pwds(&old, &new), 1);
	if (argc == 2 && ft_strcmp(argv[1], "-") == 0)
		ft_printf("%s\n", new);
	return (0);
}
