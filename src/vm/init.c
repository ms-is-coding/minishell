/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:33:13 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/13 16:15:53 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "vm/vm.h"

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
