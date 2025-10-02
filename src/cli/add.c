/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:56:07 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 14:54:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli/cli.h"

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
