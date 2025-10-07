/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:53:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 14:27:06 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "builtins.h"

int	builtin_env(t_shell *sh, int argc, char **argv, char **envp)
{
	size_t	len;

	(void)sh;
	(void)argc;
	(void)argv;
	while (*envp)
	{
		len = ft_strlen(*envp);
		(*envp)[len] = '\n';
		write(1, *envp, len + 1);
		envp++;
	}
	return (0);
}
