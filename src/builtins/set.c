/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:59:33 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/02 13:00:20 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	builtin_set(t_shell *sh, int argc, char **argv, char **envp)
{
	(void)sh;
	(void)argc;
	(void)argv;
	(void)envp;
	ft_dprintf(2, "set is not implemented yet\n");
	return (1);
}
