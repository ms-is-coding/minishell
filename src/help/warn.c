/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:05:43 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/20 19:07:20 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "help/help.h"
#include "ansi.h"
#include "libft_printf.h"

struct s_help
{
	const char	*msg;
	const char	*url;
}	help[HELP_COUNT] = {
[HELP_HOME_EXPAND] = {"If HOME is unset, the results are unspecified",
	"https://tinyurl.com/2ywa3tm8"},
[HELP_EXPORT_NOARG] = {"When no arguments are given, the results are unspecified.",
	"https://tinyurl.com/bdrpusef"}
};

void	help_warn(t_help_code code)
{

	ft_dprintf(2, ANSI_YELLOW"WARNING: "ANSI_RESET"%s"
		"\n\tVisit "ANSI_CYAN"%s"ANSI_RESET" for more details\n",
		help[code].msg, help[code].url);
}
