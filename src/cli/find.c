/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:10:31 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 14:06:12 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli/cli_internal.h"
#include "core/string.h"

/**
 * @brief Finds a CLI option by its long name.
 *
 * @param cli Pointer to the CLI structure
 * @param name Long name of the option to find
 * @return Pointer to the found CLI option, or NULL if not found
 */
t_cli_option	*cli_find(t_cli *cli, const char *name)
{
	t_cli_option	*opt;
	int				i;

	i = 1;
	while (++i < cli->opt_i)
	{
		opt = &cli->options[i];
		if (opt->long_name && ft_strcmp(opt->long_name, name) == 0)
			return (opt);
	}
	return (NULL);
}

/**
 * @brief Finds a CLI option by its short name.
 *
 * @param cli Pointer to the CLI structure
 * @param short_name Short name of the option to find
 * @return Pointer to the found CLI option, or NULL if not found
 */
t_cli_option	*cli_find_short(t_cli *cli, char short_name)
{
	t_cli_option	*opt;
	int				i;

	i = -1;
	while (++i < cli->opt_i)
	{
		opt = &cli->options[i];
		if (opt->short_name == short_name)
			return (opt);
	}
	return (NULL);
}
