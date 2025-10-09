/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:37:21 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/09 01:58:01 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_INTERNAL_H
# define CLI_INTERNAL_H

# include "cli.h"

t_cli_option	*cli_find(t_cli *cli, const char *name);
t_cli_option	*cli_find_short(t_cli *cli, char short_name);

void			cli_add(t_cli *cli, const char *long_name,
					char short_name, bool has_value);
t_result		cli_parse(t_cli *cli, int argc, char **argv);

#endif // CLI_INTERNAL_H
