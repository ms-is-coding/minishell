/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:33:13 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/24 16:27:28 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "vm/vm.h"

/**
 * @brief Initializes the virtual machine instance.
 *
 * @param vm Pointer to the virtual machine instance
 * @return Result of the initialization operation.
 */
t_result	vm_init(t_vm *vm)
{
	vm->prev_fd = 0;
	vm->pipe_fd[STDIN_FILENO] = STDIN_FILENO;
	vm->pipe_fd[STDOUT_FILENO] = STDOUT_FILENO;
	vm->pids = vec_new(16);
	vm->exit_codes = vec_new(16);
	vm->active = false;
	vm->redir_count = 0;
	return (RESULT_OK);
}
