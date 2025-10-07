/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:20:05 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 12:39:55 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env/env.h"

int	builtin_pwd(t_shell *sh, int argc, char **argv, char **envp)
{
	const char	*pwd;

	(void)envp;
	(void)argc;
	(void)argv;
	pwd = env_get(&sh->env, "PWD");
	if (!pwd)
		return (1); // error
	ft_printf("%s\n", pwd);
	return (0);
}
