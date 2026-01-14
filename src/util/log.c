/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:48:14 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:40:58 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include <sys/types.h>

#define FMT_MAX 512

t_verbosity	log_verbosity(t_verbosity v)
{
	static t_verbosity	save = VERBOSITY_GET;

	if (v != VERBOSITY_GET)
		save = v;
	return (save);
}

void	log_error(const char *fmt, ...)
{
	va_list	ap;
	char	fmt_buf[FMT_MAX];

	ft_snprintf(fmt_buf, FMT_MAX, "%s\n", fmt);
	va_start(ap, fmt);
	ft_vdprintf(2, fmt_buf, ap);
	va_end(ap);
}

void	log_verbose(const char *line)
{
	ft_dprintf(2, "%s\n", line);
}

void	log_xtrace(t_shell *sh, const char *fmt, ...)
{
	(void)sh;
	(void)fmt;

	// todo
}
