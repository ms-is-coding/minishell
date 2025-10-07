/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:45:30 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/07 16:13:07 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "shell.h"
#include <stdbool.h>

#define FLAG_P		1
#define FLAG_ERR	2

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

static void	print_aliases(t_vector aliases)
{
	//placeholder
}

int	builtin_alias(t_shell *sh, int argc, char **argv)
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
	if (!argv)
		return (print_aliases(sh->alias), 0); //print all aliases
	status = 0;
	while (*argv)
	{
		if (!is_valid_var(*argv))
			status = 1; //invalid alias name
		else if (!alias_set()) // strchr for '=' ?
			status = 1; //failed to set alias
		else if (!alias_get())
			status = 1; //failed to get alias 
		argv++;
	}
	return (status);
}
