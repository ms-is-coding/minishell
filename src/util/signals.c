/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:18:33 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/15 12:20:35 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/signals.h"
#include <stdlib.h>

/**
 * @brief Returns the string representation of a kill signal.
 *
 * @param sig Signal number
 * @return String representation of the signal.
 */
const char	*kill_signals(int sig)
{
	if (sig < 0 || sig >= 65)
		return (NULL);
	return ((const char *[65]){[1] = "HUP", [2] = "INT", [3] = "QUIT",
		[4] = "ILL", [5] = "TRAP", [6] = "ABRT", [7] = "BUS",
		[8] = "FPE", [9] = "KILL", [10] = "USR1", [11] = "SEGV", [12] = "USR2",
		[13] = "PIPE", [14] = "ALRM", [15] = "TERM", [16] = "STKFLT",
		[17] = "CHLD", [18] = "CONT", [19] = "STOP", [20] = "TSTP",
		[21] = "TTIN", [22] = "TTOU", [23] = "URG", [24] = "XCPU",
		[25] = "XFSZ", [26] = "VTALRM", [27] = "PROF", [28] = "WINCH",
		[29] = "POLL", [30] = "PWR", [31] = "SYS", [34] = "RTMIN",
		[64] = "RTMAX"}[sig]);
}
