/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:33:13 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 12:48:58 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H

# include "shell.h"

typedef enum e_verbosity
{
	VERBOSITY_GET,
	VERBOSITY_VERBOSE,
	VERBOSITY_XTRACE,
}	t_verbosity;

t_verbosity	log_verbosity(t_verbosity v);

void		log_error(const char *fmt, ...)
			__attribute__((format(printf, 1, 2)));
void		log_verbose(const char *line);
void		log_xtrace(t_shell *sh, const char *fmt, ...)
			__attribute__((format(printf, 2, 3)));

#endif
