/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:26:41 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 11:23:37 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/signals.h"
#include "vm/vm_internal.h"
#include <stddef.h>
#include <sys/wait.h>
#include "core/stdio.h"

/**
 * @brief Waits for all child processes to finish and collects their exit codes.
 *
 * @param vm Pointer to the virtual machine instance
 * @param program Pointer to the program being executed (unused)
 */
void	vm_wait(
	t_vm *vm,
	__attribute__((unused)) t_program *program)
{
	int		i;
	int		stat;
	int		code;

	i = -1;
	vm->last_exit_code = (int32_t)(int64_t)vec_get(vm->exit_codes, -1);
	while (++i < (int)vec_length(vm->pids))
	{
		code = 1;
		if (waitpid((int32_t)(int64_t)vec_get(vm->pids, i), &stat, 0) == -1)
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
			ft_dprintf(2, "[%i] %s (core dumped)\n", (int32_t)(int64_t)
				vec_get(vm->pids, i), kill_signals(code - 128));
		vec_push(vm->exit_codes, (void *)(int64_t)code);
	}
	vec_clear(vm->pids);
}
