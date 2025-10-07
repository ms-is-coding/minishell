/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:53:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 12:38:43 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_env(t_shell *sh, int argc, char **argv, char **envp)
{
	(void)sh;
	(void)argc;
	(void)argv;
	while (*envp)
		ft_printf("%s\n", *envp++);
	return (0);
}
