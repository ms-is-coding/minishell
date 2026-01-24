/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:58:16 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/24 16:26:58 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "core/stdio.h"
#include "core/string.h"
#include "shell.h"
#include "vm/vm_internal.h"

/**
 * @brief Saves the current file descriptors that will be redirected.
 *
 * @param vm Pointer to the virtual machine instance
 * @param saved_fds Array to store the saved file descriptors
 */
static void	compute_save(t_vm *vm, int saved_fds[3])
{
	int			i;
	int			t;

	ft_memcpy(saved_fds, &(int [3]){-1, -1, -1}, sizeof(int) * 3);
	i = -1;
	while (++i < vm->redir_count)
	{
		t = vm->redirs[i].target_fd;
		if (t >= 0 && t <= 2 && saved_fds[t] == -1)
			saved_fds[t] = dup(t);
	}
	if (vm->prev_fd != 0 && saved_fds[0] == -1)
		saved_fds[0] = dup(0);
	if (vm->pipe_fd[1] != 1)
		saved_fds[1] = dup(1);
}

/**
 * @brief Resets the file descriptors to their saved state after redirection.
 *
 * @param vm Pointer to the virtual machine instance
 * @param saved_fds Array of saved file descriptors
 */
static void	reset_save(t_vm *vm, int saved_fds[3])
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (saved_fds[i] != -1)
		{
			dup2(saved_fds[i], i);
			close(saved_fds[i]);
		}
	}
	i = -1;
	while (++i < vm->redir_count)
	{
		if (vm->redirs[i].file_fd >= 0)
			close(vm->redirs[i].file_fd);
	}
	vm->redir_count = 0;
}

/**
 * @brief Executes a built-in command in the virtual machine.
 *
 * @param sh Pointer to the shell structure
 * @param vm Pointer to the virtual machine instance
 * @param env Array of environment variables
 * @return Exit status code of the built-in command.
 */
void	execute_builtin(void *sh_ptr, t_vm *vm, char **env)
{
	t_shell			*sh;
	t_builtin_fn	builtin;
	int				exit_code;
	int				saved_fds[3];

	sh = sh_ptr;
	compute_save(vm, saved_fds);
	builtin = _builtin_find(vm->frame.argv[0]);
	setup_fds(vm);
	exit_code = builtin(sh, vm->frame.argc, vm->frame.argv, env);
	reset_save(vm, saved_fds);
	close_pipes(vm);
	reset_fds(vm);
	if (sh->should_exit)
	{
		sh_destroy(sh);
		ft_dprintf(2, "exit\n");
		_exit(exit_code);
	}
	vm->redir_count = 0;
	vec_push(vm->exit_codes, (void *)(intptr_t)exit_code);
}

/**
 * @brief Runs an empty command in the virtual machine.
 *
 * @param vm Pointer to the virtual machine instance
 */
void	run_empty_command(t_vm *vm)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_fds(vm);
		sh_destroy(vm->shell);
		_exit(0);
	}
	if (pid > 0)
		vec_push(vm->pids, (void *)(intptr_t)pid);
	reset_fds(vm);
	allocator_arena_free(vm->allocator, vm->frame.arena);
	return ;
}
