/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:20:05 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/30 18:30:10 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "env/env.h"
#include <stddef.h>

int	builtin_pwd(t_shell *sh, int argc, char **argv, char **envp)
{
	char	buf[PATH_MAX];
	size_t	len;

	(void)argc;
	(void)argv;
	(void)envp;
	len = ft_strlcpy(buf, env_get(&sh->env, "PWD"), PATH_MAX);
	if (len > PATH_MAX)
		return (builtin_error(ctx("pwd", NULL), ERR_TOO_LONG, 1));
	if (!buf[0])
	{
		if (!getcwd(buf, PATH_MAX))
			return (builtin_error(ctx("pwd", NULL), ERR_PERROR, 1));
	}
	buf[len] = '\n';
	write(1, buf, len + 1);
	return (0);
}

//need to check edge cases to see if it works
