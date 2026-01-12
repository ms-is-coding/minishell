/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:10:31 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 16:53:00 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli/cli_internal.h"
#include "core/string.h"

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
