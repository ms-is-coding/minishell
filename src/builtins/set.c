/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:59:33 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 17:11:03 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "core/stdio.h"

int	builtin_set(
	__attribute__((unused)) t_shell *sh,
	__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv,
	__attribute__((unused)) char **envp)
{
	ft_dprintf(2, "set is not implemented yet\n");
	return (1);
}
