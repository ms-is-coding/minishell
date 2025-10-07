/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:25:53 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/07 15:19:42 by mattcarniel      ###   ########.fr       */
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
			ft_printf("declare -x %.*s=\"%s\"\n", (int)(eq - *envp), *envp, eq + 1);
		else
			ft_printf("declare -x %s\n", *envp);
		envp++;
	}
}


int	builtin_export(t_shell *sh, int argc, char **argv, char **envp)
{
	char	flags;
	char	*name;
	int		status;

	(void)argc;
	name = argv[0];
	argv++;
	flags = set_flags(&argc, &argv);
	if (flags & FLAG_ERR)
		return (2); //Invalid option
	if (!argv)
		return (print_exported(&sh->env), 0);
	status = 0;
	while (*argv)
	{
		if (!is_valid_var(*argv))
			status = 1; //Invalid variable name
		else if (flags & FLAG_N  && !env_set()) //placeholder
			status = 1; //print export -n failed
		else if (!env_set(&sh->env, )) //placeholder
			status = 1; //print export failed
		argv++;
	}
	return (status);
}
