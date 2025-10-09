/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:45:30 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/09 15:44:46 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias/alias.h"
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

static void	print_aliases(t_alias *alias)
{
	size_t	i;

	i = 0;
	while (i < alias->capacity)
	{
		if (alias->buckets[i].key && !alias->buckets[i].is_tombstone)
		{
			if (alias->buckets[i].value)
				ft_printf("alias %s='%s'\n", alias->buckets[i].key, alias->buckets[i].value);
			else
				ft_printf("alias %s\n", alias->buckets[i].key);
		}
		i++;
	}
}

static int	seperate_alias(char *arg, char **key, char **value)
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
	return (1);
}

int	builtin_alias(t_shell *sh, int argc, char **argv, char **envp)
{
	char	flags;
	char 	*alias;
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
		return (print_aliases(&sh->alias), 0); //print all aliases
	status = 0;
	while (*argv)
	{
		if (!is_valid_var(*argv))
			status = 1; //invalid alias name
		else
		{
			seperate_alias(*argv, &key, &value);
			if (value)
			{
				if (alias_set(&sh->alias, key, value) != RESULT_OK) // strchr for '=' ?
					status = 1; //failed to set alias
			}
			else
			{
				value = ft_strdup(alias_get(&sh->alias, key)); //is this an issue ?
				if (value)
					ft_printf("alias %s='%s'\n", key, value);
				else
					status = 1; //alias not found
			}
		}
		argv++;
	}
	return (status);
}
