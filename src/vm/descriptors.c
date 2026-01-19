/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descriptors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:59:35 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/18 20:51:32 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm.h"
#include "vm/vm_internal.h"

/**
 * @brief Closes the pipes used in the virtual machine.
 *
 * @param vm Pointer to the virtual machine instance
 */
void	close_pipes(t_vm *vm)
{
	if (vm->prev_fd > 2)
		close(vm->prev_fd);
	if (vm->pipe_fd[STDIN_FILENO] > 2)
		close(vm->pipe_fd[STDIN_FILENO]);
	if (vm->pipe_fd[STDOUT_FILENO] > 2)
		close(vm->pipe_fd[STDOUT_FILENO]);
}

/**
 * @brief Sets up the file descriptors for the command execution.
 *
 * @param vm Pointer to the virtual machine instance
 */
void	setup_fds(t_vm *vm)
{
	int	i;

	if (vm->prev_fd != STDIN_FILENO)
		dup2(vm->prev_fd, STDIN_FILENO);
	if (vm->pipe_fd[STDOUT_FILENO] != STDOUT_FILENO)
		dup2(vm->pipe_fd[STDOUT_FILENO], STDOUT_FILENO);
	i = -1;
	while (++i < vm->redir_count)
		dup2(vm->redirs[i].file_fd, vm->redirs[i].target_fd);
	close_pipes(vm);
}

/**
 * @brief Resets the file descriptors in the virtual machine after command
 * execution.
 *
 * @param vm Pointer to the virtual machine instance
 */
void	reset_fds(t_vm *vm)
{
	int	i;

	if (vm->prev_fd != STDIN_FILENO)
		close(vm->prev_fd);
	if (vm->pipe_fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(vm->pipe_fd[STDOUT_FILENO]);
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
