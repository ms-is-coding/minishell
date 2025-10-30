/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readonly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:28:27 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/30 09:32:49 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "builtins/export_internal.h"
#include "env/env.h"

static bool	is_valid_var(const char *str)
{
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

int	builtin_readonly(t_shell *sh, int argc, char **argv, char **envp)
{
	t_env_bucket	*bucket;
	int				i;
	int				status;
	char			*key;
	char			*value;

	i = 1;
	(void)envp;
	status = 0;
	while (i < argc)
	{
		bucket = env_find_key(&sh->env, argv[i]);
		if (bucket)
		{
			bucket->flags |= ENV_FLAG_RDONLY;
		}
		else
		{
			if (!is_valid_var(argv[i]))
				status = builtin_error(ctx(argv[0], argv[i]), ERR_INVALID_ID, 1);
			else
			{
				separate_export(argv[i], &key, &value);
				if (env_set(&sh->env, key, value, ENV_FLAG_RDONLY) != RESULT_OK)
					status = builtin_error(ctx(argv[0], argv[i]), ERR_BAD_SET, 1);
			}
		}
		i++;

	}
	return (status);
}
