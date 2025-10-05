/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:06:13 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/03 20:44:26 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"
#include <unistd.h>

void	vm_redir_in(t_vm *vm, t_program *program)
{
	int	fd;

	// todo
	ft_memcpy(&fd, program->data + program->pc + 1, sizeof(int));
	dup2(vm->file_fd, fd);
	vm->file_out = fd;
	program->pc += 4;
}

void	vm_redir_out(t_vm *vm, t_program *program)
{
	int	fd;

	(void)vm;
	ft_memcpy(&fd, program->data + program->pc + 1, sizeof(int));
	dup2(vm->file_fd, fd);
	vm->file_in = fd;
	program->pc += 5;
}
