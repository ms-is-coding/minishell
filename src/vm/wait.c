/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:26:41 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 17:50:57 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"
#include <signal.h>
#include <sys/wait.h>
#include "core/stdio.h"

void	vm_dispatch(t_vm *vm, int sig)
{
	int	i;

	i = 0;
	while (i < (int)vec_length(vm->pids))
	{
		kill((int64_t)vec_get(vm->pids, i), sig);
		i++;
	}
}

static const char	*kill_signals(int sig)
{
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

void	vm_wait(
	t_vm *vm,
	__attribute__((unused)) t_program *program)
{
	int		i;
	int		stat;
	int		code;

	i = -1;
	while (++i < (int)vec_length(vm->pids))
	{
		code = 1;
		if (waitpid((int64_t)vec_get(vm->pids, i), &stat, 0) == -1)
			code = 1;
		else if (WIFEXITED(stat))
			code = WEXITSTATUS(stat);
		else if (WIFSIGNALED(stat))
			code = 128 + WTERMSIG(stat);
		else if (WIFSTOPPED(stat))
			code = 128 + WSTOPSIG(stat);
		else if (WIFCONTINUED(stat))
			code = 0;
		if (WCOREDUMP(stat))
			ft_dprintf(2, "[%li] %s (core dumped)\n",
				(int64_t)vec_get(vm->pids, i), kill_signals(code - 128));
		vec_push(vm->exit_codes, (void *)(int64_t)code);
	}
	vec_clear(vm->pids);
}
