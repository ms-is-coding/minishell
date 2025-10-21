/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readonly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:28:27 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/21 22:38:06 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "env/env.h"

int	builtin_readonly(t_shell *sh, int argc, char **argv, char **envp)
{
	t_env_bucket	*bucket;
	int				i;

	i = 1;
	(void)envp;
	while (i < argc)
	{
		bucket = env_find_key(&sh->env, argv[i]);
		if (!bucket)
		{
			// create empty variable
			i++;
			continue ;
		}
		bucket->flags |= ENV_FLAG_RDONLY;
		i++;
	}
	return (0);
}
