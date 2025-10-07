/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:16:58 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/07 16:12:50 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "shell.h"
#include <stdbool.h>

#define FLAG_A		1
#define FLAG_ERR	2

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

int	builtin_unalias(t_shell *sh, int argc, char **argv)
{
	char	flags;
	char 	*alias;
	int		status;

	(void)argc;
	alias = argv[0];
	argv++;
	flags = set_flags(&argc, &argv);
	if (flags & FLAG_ERR)
		return (2); //invalid option
	if (flags & FLAG_A)
		return (alias_clear(), 0);
	if (!argv)
		return (1); //invalid use, needs args or -a flag
	while (*argv)
	{
		if (!alias_remove()) // strchr for '=' ?
			status = 1; //failed to unset alias
		argv++;
	}
	return (status);
}
