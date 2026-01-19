/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:42:36 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/19 23:02:03 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include "builtins/builtins.h"
#include "builtins/type_internal.h"
#include "core/string.h"
#include "core/stdio.h"

/**
 * @brief Parses the command-line options and gets the corresponding flags.
 *
 * @param opt The command-line option string
 * @param flags Pointer to the flags variable to be updated
 * @return true if valid flags were found, false otherwise
 */
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

/**
 * @brief Sets the flags based on the command-line arguments.
 *
 * @param argv Pointer to the array of command-line arguments
 * @return The combined flags.
 */
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

/**
 * @brief Tries to find and report a builtin command.
 *
 * @param name The name of the command to check
 * @param flags Flags for type information
 * @return true if the command is a builtin, false otherwise.
 */
static bool	try_builtin(char *name, char flags)
{
	t_builtin_fn	fn;

	fn = _builtin_find(name);
	if (!fn)
		return (false);
	type_info(name, NULL, TYPE_BUILTIN, flags);
	return (true);
}

/**
 * @brief Tries to find and execute a command in the system PATH.
 *
 * @param arg Command argument (executable name)
 * @param env_path The PATH environment variable
 * @param flags Flags for type information
 * @return true if the command is found and executable, false otherwise.
 */
static bool	try_exec(const char *arg, const char *env_path, char flags)
{
	static char	path[PATH_MAX];
	size_t		len;

	if (!arg || !env_path)
		return (false);
	while (*env_path)
	{
		len = ft_strcspn(env_path, ":");
		ft_snprintf(path, PATH_MAX, "%.*s/%s", (int)len, env_path, arg);
		if (access(path, X_OK) == 0)
		{
			type_info(arg, path, TYPE_EXEC, flags);
			return (true);
		}
		env_path += len;
		if (*env_path == ':')
			env_path++;
	}
	return (false);
}

/**
 * @brief Identifies the type of commands provided as arguments.
 *
 * @param sh Pointer to the shell structure
 * @param argc Argument count (unused)
 * @param argv Argument vector
 * @param envp Environment variables (unused)
 * @return Exit status of the command.
 */
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

	found = false;
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
