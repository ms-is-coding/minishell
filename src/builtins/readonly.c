/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readonly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:28:27 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 17:10:22 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "env/env.h"
#include "core/ctype.h"
#include "core/string.h"

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

static int	separate_export(const char *arg, char **key, char **value)
{
	char	*eq;

	if (!is_valid_var(arg))
		return (builtin_error(ctx("readonly", arg), ERR_INVALID_ID, 1));
	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*eq = '\0';
		*value = ft_strdup(eq + 1);
	}
	else
		value = NULL;
	*key = ft_strdup(arg);
	return (0);
}

int	builtin_readonly(
	t_shell *sh,
	__attribute__((unused)) int argc,
	char **argv,
	__attribute__((unused)) char **envp)
{
	t_env_bucket	*bucket;
	int				status;
	char			*key;
	char			*value;

	argv++;
	status = 0;
	while (*argv)
	{
		bucket = env_find_key(&sh->env, *argv);
		if (bucket)
			bucket->flags |= ENV_FLAG_RDONLY;
		else
		{
			separate_export(*argv, &key, &value);
			if (env_set(&sh->env, key, value, ENV_FLAG_RDONLY) != RESULT_OK)
				status = builtin_error(ctx("readonly", *argv), ERR_BAD_SET, 1);
		}
		argv++;
	}
	return (status);
}
