/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   false.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 22:16:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/18 18:30:02 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	builtin_false(t_shell *sh, int argc, char **argv, char **envp)
{
	(void)sh;
	(void)argc;
	(void)argv;
	(void)envp;
	return (1);
}
