/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:00:05 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/01 11:02:04 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "cli/cli.h"

int	builtin_logout(t_shell *sh, int argc, char **argv, char **envp)
{
	if (!cli_is_set(&sh->cli, "login"))
	{
		ft_dprintf(2, "logout: not login shell. Use `exit` instead\n");
		return (1);
	}
	exit(123);
	(void)argc;
	(void)argv;
	(void)envp;
}

