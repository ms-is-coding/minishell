/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:26:41 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/16 15:48:22 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

void	vm_dispatch(t_vm *vm, int sig)
{
	int	i;

	i = 0;
	while (i < (int)vm->pids.length)
	{
		kill(ft_vector_at(&vm->pids, i).value.i32, sig);
		i++;
	}
}

void	vm_wait(t_vm *vm, t_program *program)
{
	int		i;
	int		stat;
	int		code;
	pid_t	pid;

	i = -1;
	(void)program;
	while (++i < (int)vm->pids.length)
	{
		pid = ft_vector_at(&vm->pids, i).value.i32;
		code = 1;
		if (waitpid(pid, &stat, 0) == -1)
			;
		else if (WIFEXITED(stat))
			code = WEXITSTATUS(stat);
		else if (WIFSIGNALED(stat))
			code = 128 + WTERMSIG(stat);
		else if (WIFSTOPPED(stat))
			code = 128 + WSTOPSIG(stat);
		else if (WIFCONTINUED(stat))
			code = 0;
		if (WCOREDUMP(stat))
			ft_printf("[%i] %s (core dumped)\n", pid, strsignal(code - 128));
		ignore((void *)ft_vector_push(&vm->exit_codes,
			ft_gen_val(TYPE_OTHER, (t_any){.i32 = code})));
	}
	vm->pids.length = 0;
}
