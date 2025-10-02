/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:17:53 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 14:49:09 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli/cli_internal.h"

_Bool	cli_is_set(t_cli *opts, const char *name)
{
	t_cli_option	*opt;

	opt = cli_find(opts, name);
	if (!opt)
		return (0);
	return (opt->is_set);
}

bool	cli_is_set_short(t_cli *cli, char short_name)
{
	t_cli_option	*opt;

	opt = cli_find_short(cli, short_name);
	if (!opt)
		return (0);
	return (opt->is_set);
}

char	*cli_get(t_cli *opts, const char *name)
{
	t_cli_option	*opt;

	opt = cli_find(opts, name);
	return (opt->value);
}

char	*cli_get_short(t_cli *opts, char name)
{
	t_cli_option	*opt;

	opt = cli_find_short(opts, name);
	if (!opt)
		return (NULL);
	return (opt->value);
}
