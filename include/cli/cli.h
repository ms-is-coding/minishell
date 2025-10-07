/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:01:08 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/05 20:26:54 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_H
# define CLI_H

# include "common.h"
# include "libft.h"
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
	char			**positional;
	t_cli_option	options[CLI_OPTION_COUNT];

	int				opt_i;
	int				pos_i;
}	t_cli;

t_result	cli_init(t_cli *cli, int argc, char **argv);
void		cli_destroy(t_cli *cli);

char		*cli_get(t_cli *cli, const char *name);
char		*cli_get_short(t_cli *cli, char short_name);

bool		cli_is_set(t_cli *cli, const char *name);
bool		cli_is_set_short(t_cli *cli, char short_name);

#endif // CLI_H
