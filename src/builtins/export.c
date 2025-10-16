/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:25:53 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/16 12:49:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env/env.h"
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

static void	print_exported(char **envp)
{
	char	*eq;

	while (envp && *envp)
	{
		eq = ft_strchr(*envp, '=');
		if (eq)
			ft_printf("export %.*s=\"%s\"\n", (int)(eq - *envp), *envp, eq + 1);
		else
			ft_printf("export %s\n", *envp);
		envp++;
	}
}

static void	separate_export(char *arg, char **key, char **value)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		*eq = '\0';
	else
		*value = NULL;
	*key = ft_strdup(arg);
	if (eq)
		*value = ft_strdup(eq + 1); //no sanity checks
	else
		*value = NULL;
}


int	builtin_export(t_shell *sh, int argc, char **argv, char **envp)
{
	char	flags;
	char	*alias;
	char	*key;
	char	*value;
	int		status;

	(void)argc;
	alias = argv[0];
	argv++;
	flags = set_flags(&argc, &argv);
	if (flags & FLAG_ERR)
		return (builtin_error(ctx(alias, *argv), ERR_INVALID_OPT, 2));
	if (!(*argv))
		return (print_exported(envp), 0);
	status = 0;
	while (*argv)
	{
		if (!is_valid_var(*argv))
			status = 1;//Invalid variable name
		else
		 {
			separate_export(*argv, &key, &value);
			if (flags & FLAG_N  && env_set(&sh->env, key, value, false) != RESULT_OK) //placeholder
				status = 1; //print export -n failed
			else if (env_set(&sh->env, key, value, true) != RESULT_OK) //placeholder
				status = 1; //print export failed
		 }
		argv++;
	}
	return (status);
}
