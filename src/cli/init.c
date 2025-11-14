/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:06:01 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/07 06:42:23 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli/cli_internal.h"
#include "allocator/allocator.h"
#include "libft.h"

#ifdef NDEBUG

static void	cli_init_debug(t_cli *cli)
{
	(void)cli;
}

#else

static void	cli_init_debug(t_cli *cli)
{
	cli_add(cli, "disassemble", 'd', 0);
}

#endif

t_result	cli_init(t_cli *cli, int argc, char **argv)
{
	cli->name = argv[0];
	cli->opt_i = 0;
	cli->pos_i = 0;
	cli->positional = allocator_malloc(sizeof(char *) * 8);
	if (!cli->positional)
		return (RESULT_ERROR);
	cli->pos_capacity = 8;
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

void	cli_destroy(t_cli *cli)
{
	allocator_free_ptr(cli->positional);
}
