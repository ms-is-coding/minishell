/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:53:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/30 16:18:19 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#include "builtins/builtins.h"
#include "libft.h"

#define FLAG_I		1
#define FLAG_ERR	2

static bool	get_flags(const char *opt, char *flags)
{
	int		i;

	if (!opt || opt[0] != '-' || ft_strcmp(opt, "-") == 0)
		return (false);
	i = 1;
	while (opt[i])
	{
		if (opt[i] == 'i')
			*flags |= FLAG_I;
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

static bool	is_valid_assignment(const char *str)
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
	if (*str == '=')
		return (true);
	return (false);
}

static int	is_existing_var(char **envp, const char *assignment)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (assignment[len] && assignment[len] != '=')
		len++;
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], assignment, len) == 0
			&& (envp[i][len] == '=' || envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static void	print_env(char **envp)
{
	size_t	len;

	while (*envp)
	{
		len = ft_strlen(*envp);
		(*envp)[len] = '\n';
		write(1, *envp, len + 1);
		envp++;
	}
}

int	builtin_env(t_shell *sh, int argc, char **argv, char **envp)
{
	char	**envp_copy;
	size_t	count;
	size_t	i;
	char	flags;
	char	*alias;
	int		exist;

	(void)sh;
	(void)argc;
	alias = argv[0];
	flags = set_flags(&argc, &argv);
	if (flags & FLAG_ERR)
		return (builtin_error(ctx(alias, *argv), ERR_INVALID_OPT, 125));
	count = 0;
	if (!(flags & FLAG_I) && envp)
		while (envp[count++]);
	i = 0;
	while (argv[i] && is_valid_assignment(argv[i]))
	{
		if (is_existing_var(envp, argv[i]) == -1)
			count++;
		i++;
	}
	envp_copy = malloc(sizeof(char *) * (count + 1)); //sanity check ?
	i = 0;
	if (!(flags & FLAG_I) && envp)
	{
		while (envp[i])
		{
			envp_copy[i] = envp[i];
			i++;
		}
	}
	while (argv && *argv && is_valid_assignment(*argv))
	{
		exist = is_existing_var(envp_copy, *argv);
		if (exist == -1)
			envp_copy[i++] = *argv;
		else
			envp_copy[exist] = *argv;
		argv++;
	}
	envp_copy[i] = NULL;
	if (!*argv)
	{
		print_env(envp_copy);
		free(envp_copy);
	}
	else
	{
		if (!access(*argv, F_OK))
			return (builtin_error(ctx(alias, *argv), ERR_FILE_EXISTS, 126));
		execve(*argv, argv, envp_copy);
		free(envp_copy);
		return (builtin_error(ctx(alias, *argv), ERR_NOT_FOUND, 127)); // correct error msg ? how to 126 ?

	}
	return (0);
}	
