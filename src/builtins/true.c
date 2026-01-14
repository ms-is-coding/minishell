/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 22:15:39 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 16:47:58 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

/**
 * @brief Builtin command that always returns a success status.
 *
 * @param sh Pointer to the shell structure (unused)
 * @param argc Argument count (unused)
 * @param argv Argument vector (unused.
 * @param envp Environment pointer (unused)
 * @return Always returns 0 (success).
 */
int	builtin_true(
	__attribute__((unused)) t_shell *sh,
	__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv,
	__attribute__((unused)) char **envp)
{
	return (0);
}
