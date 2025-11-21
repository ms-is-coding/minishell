/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:05:43 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/22 00:24:12 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/help.h"
#include "ansi.h"
#include "libft_printf.h"

struct s_help
{
	const char	*msg;
	const char	*url;
}	help[HELP_COUNT] = {
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
		help[code].msg, help[code].url);
}
