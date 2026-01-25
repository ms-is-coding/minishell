/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:25:53 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/25 13:29:55 by smamalig         ###   ########.fr       */
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
static int	set_export(t_env *env, const char *arg)
{
	char	*key;
	char	*value;
	char	*eq;

	if (!is_valid_var(arg))
		return (builtin_error(ctx("export", arg), ERR_INVALID_ID, 1));
	key = ft_strdup(arg);
	if (!key)
		return (builtin_error(ctx("export", arg), ERR_OOM, 1));
	eq = ft_strchr(key, '=');
	value = NULL;
	(void)(eq && (eq[0] = '\0', value = eq + 1));
	if (!value && env_exists(env, key))
	{
		env_set_flag(env, key, ENV_FLAG_EXPORT);
		ft_free(key);
		return (0);
	}
	if (env_set(env, key, value, ENV_FLAG_EXPORT) != RESULT_OK)
	{
		ft_free(key);
		return (builtin_error(ctx("export", arg), ERR_BAD_SET, 1));
	}
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
	int		status;

	argv++;
	if (!(*argv))
		return (print_exported(&sh->env), 0);
	status = 0;
	while (*argv)
	{
		if (set_export(&sh->env, *argv) != 0)
			status = 1;
		argv++;
	}
	return (status);
}
