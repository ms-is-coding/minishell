/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:17:53 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/24 16:18:53 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli/cli_internal.h"

/**
 * @brief Checks if a CLI option is set by its long name.
 *
 * @param opts Pointer to the CLI options structure
 * @param name Long name of the option to check
 * @return true if the option is set, false otherwise.
 */
bool	cli_is_set(t_cli *opts, const char *name)
{
	t_cli_option	*opt;

	opt = cli_find(opts, name);
	if (!opt)
		return (false);
	return (opt->is_set);
}

/**
 * @brief Checks if a CLI option is set by its short name.
 *
 * @param cli Pointer to the CLI options structure
 * @param short_name Short name of the option to check
 * @return true if the option is set, false otherwise.
 */
bool	cli_is_set_short(t_cli *cli, char short_name)
{
	t_cli_option	*opt;

	opt = cli_find_short(cli, short_name);
	if (!opt)
		return (false);
	return (opt->is_set);
}

/**
 * @brief Retrieves the value of a CLI option by its long name.
 *
 * @param opts Pointer to the CLI options structure
 * @param name Long name of the option
 * @return Value of the option as a string.
 */
char	*cli_get(t_cli *opts, const char *name)
{
	t_cli_option	*opt;

	opt = cli_find(opts, name);
	if (!opt)
		return (NULL);
	return (opt->value);
}

/**
 * @brief Retrieves the value of a CLI option by its short name.
 *
 * @param opts Pointer to the CLI options structure
 * @param name Short name of the option
 * @return Value of the option as a string.
 */
char	*cli_get_short(t_cli *opts, char name)
{
	t_cli_option	*opt;

	opt = cli_find_short(opts, name);
	if (!opt)
		return (NULL);
	return (opt->value);
}
