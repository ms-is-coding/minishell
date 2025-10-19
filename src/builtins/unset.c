/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:20:35 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/18 18:29:40 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "libft.h"
#include <stdbool.h>

int	builtin_unset(t_shell *sh, int argc, char **argv, char **envp)
{
	char	*alias;
	int		status;
	
	(void)argc;
	(void)envp;
	alias = argv[0];
	argv++;
	while (*argv)
	{
		if (env_remove(&sh->env, *argv) != RESULT_OK)
			status = builtin_error(ctx(alias, *argv), ERR_UNKNOWN, 1); //placeholder ERR
		argv++;
	}
	return (status);
}
