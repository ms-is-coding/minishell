/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:20:35 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/15 13:09:16 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "core/string.h"
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
int	builtin_unset(
	t_shell *sh,
	__attribute__((unused)) int argc,
	char **argv,
	__attribute__((unused)) char **envp)
{
	int			status;
	t_result	result;

	argv++;
	status = 0;
	if (*argv[0] == '-' && *argv[1] != '\0')
	{
		if (ft_strcmp(*argv, "--") == 0)
			argv++;
		else
			return (builtin_error(ctx("unset", *argv), ERR_INVALID_OPT, 2));
	}
	while (*argv)
	{
		result = env_remove(&sh->env, *argv);
		if (result == RESULT_RDONLY)
			status = builtin_error(ctx("unset", *argv), ERR_READONLY, 1);
		argv++;
	}
	return (status);
}
