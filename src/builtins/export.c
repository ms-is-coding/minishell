/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:25:53 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/14 18:38:41 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "builtins/export_internal.h"
#include "env/env.h"
#include "core/string.h"
#include "core/ctype.h"
#include <stdbool.h>

#define FLAG_N		1
#define FLAG_ERR	2

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
		if (opt[i] == 'n')
			*flags |= FLAG_N;
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
 * @brief Validates if a string is a valid environment variable name.
 *
 * @param str The string to validate
 * @return true if valid, false otherwise.
 */
static bool	is_valid_var(const char *str)
{
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

/**
 * @brief Sets an environment variable to be exported.
 *
 * @param env Pointer to the environment structure
 * @param arg The argument string containing the variable assignment
 * @param flags Flags indicating export options
 * @return 0 on success, non-zero on failure.
 */
static int	set_export(t_env *env, const char *arg, char flags)
{
	char	*key;
	char	*value;
	char	*eq;

	if (!is_valid_var(arg))
		return (builtin_error(ctx("export", arg), ERR_INVALID_ID, 1));
	key = allocator_strdup(arg);
	eq = ft_strchr(key, '=');
	value = NULL;
	if (eq)
	{
		*eq = '\0';
		value = eq + 1;
	}
	if (flags & FLAG_N)
	{
		if (env_set(env, key, value, 0) != RESULT_OK)
			return (builtin_error(ctx("export", arg), ERR_BAD_SET, 1));
	}
	else if (env_set(env, key, value, ENV_FLAG_EXPORT) != RESULT_OK)
		return (builtin_error(ctx("export", arg), ERR_BAD_SET, 1));
	return (0);
}

/**
 * @brief Sets environment variables to be exported to child processes.
 *
 * @param sh Pointer to the shell structure
 * @param argc Argument count (unused)
 * @param argv Argument vector
 * @param envp Environment variables (unused)
 * @return Exit code of the export command.
 */
int	builtin_export(
	t_shell *sh,
	__attribute__((unused)) int argc,
	char **argv,
	__attribute__((unused)) char **envp)
{
	char	flags;
	int		status;

	argv++;
	flags = set_flags(&argc, &argv);
	if (flags & FLAG_ERR)
		return (builtin_error(ctx("export", *argv), ERR_INVALID_OPT, 2));
	if (!(*argv))
		return (print_exported(&sh->env), 0);
	status = 0;
	while (*argv)
	{
		if (set_export(&sh->env, *argv, flags) != 0)
			status = 1;
		argv++;
	}
	return (status);
}
