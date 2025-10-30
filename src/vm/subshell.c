/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:43:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/23 21:27:19 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm/bytecode.h"
#include "vm/vm.h"
#include "vm/vm_internal.h"
#include <stdint.h>
#include <sys/types.h>

static void	close_pipes(t_vm *vm)
{
	if (vm->prev_fd > 2)
		close(vm->prev_fd);
	if (vm->pipe_fd[STDIN_FILENO] > 2)
		close(vm->pipe_fd[STDIN_FILENO]);
	if (vm->pipe_fd[STDOUT_FILENO] > 2)
		close(vm->pipe_fd[STDOUT_FILENO]);
}

static void	setup_fds(t_vm *vm)
{
	int	i;

	ft_dprintf(2, "=== FDS (SUB) ===\n");
	ft_dprintf(2, "prev_fd: %4i\n", vm->prev_fd);
	ft_dprintf(2, "pipe[0]: %4i\n", vm->pipe_fd[0]);
	ft_dprintf(2, "pipe[1]: %4i\n", vm->pipe_fd[1]);
	i = -1;
	while (++i < vm->redir_count)
	{
		ft_dprintf(2, "[%i].file: %3i\n", i, vm->redirs[i].file_fd);
		ft_dprintf(2, "[%i].target: %3i\n", i, vm->redirs[i].target_fd);
	}
	if (vm->prev_fd != STDIN_FILENO)
		dup2(vm->prev_fd, STDIN_FILENO);
	if (vm->pipe_fd[STDOUT_FILENO] != STDOUT_FILENO)
		dup2(vm->pipe_fd[STDOUT_FILENO], STDOUT_FILENO);
	i = -1;
	while (++i < vm->redir_count)
		dup2(vm->redirs[i].file_fd, vm->redirs[i].target_fd);
	close_pipes(vm);
}

static void	reset_fds(t_vm *vm)
{
	int	i;

	if (vm->prev_fd != STDIN_FILENO)
		close(vm->prev_fd);
	if (vm->pipe_fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(vm->pipe_fd[1]);
	vm->prev_fd = vm->pipe_fd[STDIN_FILENO];
	vm->pipe_fd[STDIN_FILENO] = STDIN_FILENO;
	vm->pipe_fd[STDOUT_FILENO] = STDOUT_FILENO;
	i = -1;
	while (++i < vm->redir_count)
	{
		if (vm->redirs[i].file_fd >= 0)
			close(vm->redirs[i].file_fd);
	}
	vm->redir_count = 0;
}

static bool	is_command_in_pipeline(t_vm *vm)
{
	return (vm->prev_fd != STDIN_FILENO
		|| vm->pipe_fd[STDIN_FILENO] != STDIN_FILENO
		|| vm->pipe_fd[STDOUT_FILENO] != STDOUT_FILENO);
}

void	vm_subshell(t_vm *vm, t_program *program)
{
	int32_t		end_pc;
	pid_t		pid;
	t_vm		child_vm;

	child_vm = (t_vm){0};
	if (vm->pids.length == 0)
		vm->exit_codes.length = 0;
	child_vm.shell = vm->shell;
	child_vm.allocator = vm->allocator;
	program->pc++;
	end_pc = program_get_i32(program);
	pid = fork();
	if (pid == 0)
	{
		if ((program->data[end_pc] & OPCODE_MASK) == OP_EXEC
			&& program->data[end_pc] & EXEC_PIPELINE_BIT)
		{
			if (pipe(vm->pipe_fd) < 0)
			{
				ft_printf("pipe failed: %m\n");
				return ;
			}
		}
		setup_fds(vm);
		vm_run_range(&child_vm, program, end_pc - 1);
		vm_wait(&child_vm, NULL);
		exit(ft_vector_at(&child_vm.exit_codes, -1).value.i32);
		return ;
	}
	ft_vector_push(&vm->pids, ft_gen_val(TYPE_OTHER, (t_any){.i32 = pid}));
	reset_fds(vm);
	program->pc = end_pc;
	if (!is_command_in_pipeline(vm))
		vm_wait(vm, program);
}
