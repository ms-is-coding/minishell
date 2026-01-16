/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:37:21 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 16:58:35 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_INTERNAL_H
# define CLI_INTERNAL_H

# include "cli.h"

typedef enum e_cli_error
{
	CLI_ERR_NONE,
	CLI_ERR_INVALID_OPT,
	CLI_ERR_MISSING_VALUE,
	CLI_ERR_NO_ACCEPT,
	CLI_ERR_COUNT
}	t_cli_error;

t_cli_option	*cli_find(t_cli *cli, const char *name);
t_cli_option	*cli_find_short(t_cli *cli, char short_name);

void			cli_add(t_cli *cli, const char *long_name,
					char short_name, bool has_value);
t_result		cli_parse(t_cli *cli, int argc, char **argv);

#endif // CLI_INTERNAL_H
