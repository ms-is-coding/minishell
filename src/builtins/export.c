/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:25:53 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/12/01 19:21:31 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "builtins/export_internal.h"
#include "env/env.h"
#include "libft.h"
#include <stdbool.h>

#define FLAG_N		1
#define FLAG_ERR	2

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
