/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:20:35 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/21 22:42:15 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "libft.h"
#include <stdbool.h>

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
		{
			ft_dprintf(2, "unset: %s: cannot unset: readonly variable\n", *argv);
			status = 1;
		}
		argv++;
	}
	return (status);
}
