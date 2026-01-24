/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:48:14 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/24 16:25:23 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include <sys/types.h>

#define FMT_MAX 512

/**
 * @brief Sets or gets the current log verbosity level.
 *
 * @param v The verbosity level to set, or VERBOSITY_GET to retrieve the current
 * level
 * @return The current verbosity level.
 */
t_verbosity	log_verbosity(t_verbosity v)
{
	static t_verbosity	save = VERBOSITY_GET;

	if (v != VERBOSITY_GET)
		save = v;
	return (save);
}

/**
 * @brief Logs an error message to standard error.
 *
 * @param fmt The format string for the error message
 * @param ... Additional arguments for the format string
 */
void	log_error(const char *fmt, ...)
{
	va_list	ap;
	char	fmt_buf[FMT_MAX];

	ft_snprintf(fmt_buf, FMT_MAX, "%s\n", fmt);
	va_start(ap, fmt);
	ft_vdprintf(2, fmt_buf, ap);
	va_end(ap);
}

/**
 * @brief Logs a verbose message to standard error.
 *
 * @param line The message to log
 */
void	log_verbose(const char *line)
{
	ft_dprintf(2, "%s\n", line);
}

/**
 * @brief Logs an xtrace message.
 *
 * @param sh Pointer to the shell structure
 * @param fmt The format string for the xtrace message
 * @param ... Additional arguments for the format string
 */
void	log_xtrace(t_shell *sh, const char *fmt, ...)
{
	(void)sh;
	(void)fmt;

	// todo
}
