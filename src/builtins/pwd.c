/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:20:05 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 14:59:49 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env/env.h"

int	builtin_pwd(t_shell *sh, int argc, char **argv, char **envp)
{
	const char	*pwd;
	char		buf[PATH_MAX];

	(void)envp;
	(void)argc;
	pwd = env_get(&sh->env, "PWD");
	if (!pwd)
	{
		if (!getcwd(buf, PATH_MAX))
			return (builtin_error(ctx(argv[0], "pwd"), ERR_PERROR, 1));
		pwd = buf;
	}
	ft_printf("%s\n", pwd);
	return (0);
}
