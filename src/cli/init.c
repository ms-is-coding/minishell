/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:06:01 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 13:43:56 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli/cli_internal.h"
#include "core/stdlib.h"

#ifdef NDEBUG

/**
 * @brief Initializes debug-specific CLI options (no-op in release builds).
 *
 * @param cli Pointer to the CLI structure
 */
static void	cli_init_debug(t_cli *cli)
{
	(void)cli;
}

#else

/**
 * @brief Initializes debug-specific CLI options.
 *
 * @param cli Pointer to the CLI structure
 */
static void	cli_init_debug(t_cli *cli)
{
	cli_add(cli, "disassemble", 'd', 0);
}

#endif

/**
 * @brief Initializes the CLI structure with command-line arguments.
 *
 * @param cli Pointer to the CLI structure
 * @param argc Argument count
 * @param argv Argument vector
 * @return t_result RESULT_OK on success, RESULT_ERROR on failure.
 */
t_result	cli_init(t_cli *cli, int argc, char **argv)
{
	cli->name = argv[0];
	cli->opt_i = 0;
	cli_add(cli, "posix", 0, 0);
	cli_add(cli, "verbose", 'v', 0);
	cli_add(cli, "version", 0, 0);
	cli_add(cli, "login", 0, 0);
	cli_add(cli, NULL, 'c', 1);
	cli_init_debug(cli);
	if (cli_parse(cli, argc, argv) != RESULT_OK)
		return (RESULT_ERROR);
	return (RESULT_OK);
}
