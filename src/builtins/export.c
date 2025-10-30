/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:25:53 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/23 12:26:05 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "builtins/export_internal.h"
#include "env/env.h"
#include "help/help.h"
#include "libft.h"
#include <stdbool.h>

#define FLAG_P		1
#define FLAG_N		2
#define FLAG_ERR	4

static bool	get_flags(const char *opt, char *flags)
{
	int		i;

	if (!opt || opt[0] != '-' || ft_strcmp(opt, "-") == 0)
		return (false);
	i = 1;
	while (opt[i])
	{
		if (opt[i] == 'p')
			*flags |= FLAG_P;
		else if (opt[i] == 'n')
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

// When no arguments are given, the results are unspecified.
int	builtin_export(t_shell *sh, int argc, char **argv, char **envp)
{
	char	flags;
	char	*alias;
	char	*key;
	char	*value;
	int		status;

	(void)argc;
	(void)envp;
	alias = argv[0];
	argv++;
	flags = set_flags(&argc, &argv);
	if (flags & FLAG_ERR)
		return (builtin_error(ctx(alias, *argv), ERR_INVALID_OPT, 2));
	if (!(*argv))
	{
		if (!(flags & FLAG_P))
			help_warn(HELP_EXPORT_NOARG);
		return (print_exported(&sh->env), 0);
	}
	status = 0;
	while (*argv)
	{
		if (!is_valid_var(*argv))
			status = builtin_error(ctx(alias, *argv), ERR_INVALID_ID, 1);
		else
		{
			separate_export(*argv, &key, &value);
			if (flags & FLAG_N
				&& env_set(&sh->env, key, value, 0) != RESULT_OK)
				status = builtin_error(ctx(alias, *argv), ERR_BAD_SET, 1);
			else if (env_set(&sh->env, key, value, ENV_FLAG_EXPORT) != RESULT_OK)
				status = builtin_error(ctx(alias, *argv), ERR_BAD_SET, 1);
		}
		argv++;
	}
	return (status);
}
