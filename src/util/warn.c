/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:05:43 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 17:34:58 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/help.h"
#include "ansi.h"
#include "core/stdio.h"

struct s_help
{
	const char	*msg;
	const char	*url;
};

static struct s_help	g_help[HELP_COUNT] = {
[HELP_HOME_EXPAND] = {"If HOME is unset, the results are unspecified",
	"https://tinyurl.com/2ywa3tm8"},
[HELP_EXPORT_NOARG] = {
	"When no arguments are given, the results are unspecified",
	"https://tinyurl.com/bdrpusef"},
[HELP_HEREDOC_EOF] = {
	"Here-document delimited by end-of-file",
	"https://tinyurl.com/4bbffxcx"},
[HELP_UNSAFE_EXEC] = {
	"The shell is currently vulnerable to TOCTOU. To avoid this warning, "
	"please compile in release mode",
	"https://tinyurl.com/57fh7f4s"}
};

void	help_warn(t_help_code code)
{
	ft_dprintf(2, ANSI_YELLOW"WARNING: "ANSI_RESET"%s"
		"\n\tVisit "ANSI_CYAN"%s"ANSI_RESET" for more details\n",
		g_help[code].msg, g_help[code].url);
}
