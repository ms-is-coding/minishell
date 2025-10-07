/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   false.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 22:16:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/06 16:35:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_false(t_shell *sh, int argc, char **argv, char **envp)
{
	(void)sh;
	(void)argc;
	(void)argv;
	(void)envp;
	return (1);
}
