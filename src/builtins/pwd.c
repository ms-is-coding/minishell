/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:20:05 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/18 14:54:11 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env/env.h"
#include <stddef.h>

int	builtin_pwd(t_shell *sh, int argc, char **argv, char **envp)
{
	char	buf[PATH_MAX];
	size_t	len;

	(void)envp;
	(void)argc;
	len = ft_strlcpy(buf, env_get(&sh->env, "PWD"), PATH_MAX);
	if (len > PATH_MAX)
		return (builtin_error(ctx(argv[0], NULL), ERR_TOO_LONG, 1));
	if (!buf[0])
	{
		if (!getcwd(buf, PATH_MAX))
			return (builtin_error(ctx(argv[0], "pwd"), ERR_PERROR, 1));
	}
	buf[len] = '\n';
	write(1, buf, len + 1);
	return (0);
}

//need to check edge cases to see if it works
