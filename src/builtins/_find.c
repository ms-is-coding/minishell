/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _find.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 13:12:32 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 18:40:22 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "core/string.h"

#include <stdio.h>

struct s_builtin
{
	const char		*cmd;
	t_builtin_fn	fn;
	size_t			hash;
};

static struct s_builtin	g_builtins[] = {
{":", builtin_true, 177631ul},
	// {"alias", builtin_alias, 210706582927ul},
{"cd", builtin_cd, 5863276ul},
{"echo", builtin_echo, 6385181892ul},
{"env", builtin_env, 193490734ul},
{"exec", builtin_exec, 6385204650ul},
{"exit", builtin_exit, 6385204799ul},
{"export", builtin_export, 6953488276103ul},
{"false", builtin_false, 210712121072ul},
	// {"logout", builtin_logout, 6953751227231ul},
{"pwd", builtin_pwd, 193502992ul},
{"readonly", builtin_readonly, 7572877634356771ul},
	// {"return", builtin_return, 6953974653989ul},
	// {"set", builtin_set, 193505681ul},
{"true", builtin_true, 6385737701ul},
{"type", builtin_type, 6385745159ul},
	// {"unalias", builtin_unalias, 229485367338034ul},
{"unset", builtin_unset, 210730384244ul},
{"help", builtin_help, 6385292014ul},
{NULL, NULL, 0}
};

/**
 * @brief Finds a builtin function by its name.
 *
 * @param name The name of the builtin command.
 * @return The function pointer to the builtin function, or NULL if not found.
 */
t_builtin_fn	_builtin_find(const char *name)
{
	size_t	hash;
	int		i;

	hash = 5381;
	i = -1;
	while (name[++i])
		hash = ((hash << 5) + hash) + (uint8_t)name[i];
	i = -1;
	while (g_builtins[++i].fn)
	{
		if (g_builtins[i].hash == hash
			&& ft_strcmp(g_builtins[i].cmd, name) == 0)
			return (g_builtins[i].fn);
	}
	return (NULL);
}
