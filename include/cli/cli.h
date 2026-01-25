/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:01:08 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 13:44:00 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_H
# define CLI_H

# include "common.h"
# include "core/stdlib.h"
# include <stdbool.h>

typedef struct s_cli_option
{
	const char	*long_name;
	char		*value;
	char		short_name;
	bool		is_set;
	bool		has_value;

	char		reserved[5];
}	t_cli_option;

typedef struct s_cli
{
	char			*name;
	t_cli_option	options[CLI_OPTION_COUNT];
	int				opt_i;
	char			reserved[4];
}	t_cli;

t_result	cli_init(t_cli *cli, int argc, char **argv);

char		*cli_get(t_cli *cli, const char *name);
char		*cli_get_short(t_cli *cli, char short_name);

bool		cli_is_set(t_cli *cli, const char *name);
bool		cli_is_set_short(t_cli *cli, char short_name);

#endif // CLI_H
