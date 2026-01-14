/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:56:07 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 16:39:20 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli/cli_internal.h"

/**
 * @brief Adds a new option to the CLI structure.
 *
 * @param cli Pointer to the CLI structure.
 * @param long_name Long name of the option.
 * @param short_name Short name (character) of the option.
 * @param has_value Boolean indicating if the option requires a value.
 */
void	cli_add(
	t_cli *cli,
	const char *long_name,
	char short_name,
	bool has_value
)
{
	t_cli_option	*opt;

	opt = &cli->options[cli->opt_i++];
	opt->has_value = has_value;
	opt->long_name = long_name;
	opt->short_name = short_name;
	opt->is_set = 0;
}
