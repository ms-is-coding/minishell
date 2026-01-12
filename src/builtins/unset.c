/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:20:35 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/06 22:42:52 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include <stdbool.h>

//needs tweaking
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
