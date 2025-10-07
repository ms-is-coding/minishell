/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:01:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/06 16:36:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_exit(t_shell *sh, int argc, char **argv, char **envp)
{
	(void)argv;
	(void)sh;
	(void)argc;
	(void)envp;
	exit(0);
	return (0);
}
