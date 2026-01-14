/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:20:35 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/14 18:47:29 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include <stdbool.h>

/**
 * @brief Unsets values of shell variables.
 *
 * @param sh Pointer to the shell structure
 * @param argc Argument count (unused)
 * @param argv Argument vector
 * @param envp Environment pointer (unused)
 * @return Exit code of the command.
 */
int	builtin_unset( // FIX needs tweaking
	t_shell *sh,
	__attribute__((unused)) int argc,
	char **argv,
	__attribute__((unused)) char **envp)
{
	int			status;
	t_result	result;

	argv++;
	status = 0;
	while (*argv)
	{
		if (*argv[0] == '-')
			return (builtin_error(ctx("unset", *argv), ERR_BAD_SET, 2));
		result = env_remove(&sh->env, *argv);
		if (result == RESULT_RDONLY)
			status = builtin_error(ctx("unset", *argv), ERR_BAD_SET, 1);
		argv++;
	}
	return (status);
}
