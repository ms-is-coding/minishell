/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_internal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:33:47 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 18:12:07 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_INTERNAL_H
# define VM_INTERNAL_H

# include <stddef.h>
# include "vm.h"

typedef void	(*t_exec_handler)(t_vm *vm, t_program *program);

void	vm_dispatch(t_vm *vm, int sig);
void	vm_spawn(t_vm *vm);

void	vm_wait(t_vm *vm, t_program *program);

void	close_pipes(t_vm *vm);
void	setup_fds(t_vm *vm);
void	reset_fds(t_vm *vm);
void	execute_builtin(void *sh, t_vm *vm, char **env);
void	run_empty_command(t_vm *vm);

void	vm_command(t_vm *vm, t_program *program);
void	vm_exec(t_vm *vm, t_program *program);
void	vm_arg(t_vm *vm, t_program *program);
void	vm_filename(t_vm *vm, t_program *program);
void	vm_pipe(t_vm *vm, t_program *program);
void	vm_background(t_vm *vm, t_program *program);
void	vm_redir_out(t_vm *vm, t_program *program);
void	vm_redir_in(t_vm *vm, t_program *program);
void	vm_jump(t_vm *vm, t_program *program);
void	vm_heredoc(t_vm *vm, t_program *program);

void	vm_arg_dummy(t_vm *vm, t_program *program);
void	vm_redir_dummy(t_vm *vm, t_program *program);

/**
 * @brief Checks if the current command is part of a pipeline.
 *
 * @param vm Pointer to the virtual machine instance
 * @return true if the command is in a pipeline, false otherwise.
 */
__attribute__((__always_inline__))
inline bool	is_command_in_pipeline(t_vm *vm)
{
	return (vm->prev_fd != STDIN_FILENO
		|| vm->pipe_fd[STDIN_FILENO] != STDIN_FILENO
		|| vm->pipe_fd[STDOUT_FILENO] != STDOUT_FILENO);
}

#endif // VM_INTERNAL_H
