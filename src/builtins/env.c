/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:53:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/03 17:16:10 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#include "builtins/builtins.h"
#include "builtins/env_internal.h"
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

static int	build_env_copy(char **copy, char **envp, char ***argv, char flags)
{
	size_t	parsed;
	size_t	i;
	int		exist;

	i = 0;
	if (!(flags & FLAG_I) && envp)
	{
		while (envp[i])
		{
			copy[i] = envp[i];
			i++;
		}
	}
	parsed = 0;
	while (argv && *argv && is_valid_assignment(**argv))
	{
		exist = is_existing_var(copy, **argv);
		if (exist == -1)
			copy[i++] = **argv;
		else
			copy[exist] = **argv;
		(*argv)++;
		parsed++;
	}
	return (parsed);
}

static int	exec_env(t_shell *sh, int argc, char **argv, char **envp)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (builtin_error(ctx("env", NULL), ERR_PERROR, 125));
	else if (pid == 0)
		exit(builtin_exec(sh, argc, argv - 1, envp));
	else
		waitpid(pid, &status, 0);
	return (status);
}

int	builtin_env(t_shell *sh, int argc, char **argv, char **envp)
{
	char	**copy;
	char	flags;
	int		status;

	status = 0;
	argv++;
	flags = set_flags(&argc, &argv);
	if (flags & FLAG_ERR)
		return (builtin_error(ctx("env", *argv), ERR_INVALID_OPT, 125));
	copy = ft_calloc((get_env_size(argv, envp, flags) + 1), sizeof(char *));
	if (!copy)
		return (125);
	argc -= build_env_copy(copy, envp, &argv, flags);
	if (!*argv)
		print_env(copy);
	else
		status = exec_env(sh, argc, argv, copy);
	free(copy);
	return (WEXITSTATUS(status));
}
//calloc sanity check ? What error msg for calloc failure?
