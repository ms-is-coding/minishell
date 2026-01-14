/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   false.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 22:16:02 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 18:28:02 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

/**
 * @brief Builtin command that always returns a failure status.
 *
 * @param sh Pointer to the shell structure (unused)
 * @param argc Argument count (unused)
 * @param argv Argument vector (unused.
 * @param envp Environment pointer (unused)
 * @return Always returns 1 (failure).
 */
int	builtin_false(
	__attribute__((unused)) t_shell *sh,
	__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv,
	__attribute__((unused)) char **envp)
{
	return (1);
}
