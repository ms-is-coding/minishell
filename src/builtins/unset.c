/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:20:35 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/11/18 12:53:25 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "libft.h"
#include <stdbool.h>

//needs tweaking
int	builtin_unset(t_shell *sh, int argc, char **argv, char **envp)
{
	int			status;
	t_result	result;

	(void)argc;
	(void)envp;
	argv++;
	status = 0;
	while (*argv)
	{
		result = env_remove(&sh->env, *argv);
		if (result == RESULT_RDONLY)
			status = builtin_error(ctx("unset", *argv), ERR_BAD_SET, 1);
		argv++;
	}
	return (status);
}
