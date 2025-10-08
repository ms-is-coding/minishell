/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:17:46 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 21:55:17 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"

void	vm_pipe(t_vm *vm, t_program *program)
{
	if (pipe(vm->pipe_fd) < 0)
	{
		ft_printf("pipe failed: %m\n");
	}
	vm_spawn(vm, program);
}
