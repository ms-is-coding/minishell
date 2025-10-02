/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:17:46 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 22:18:46 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"

void	vm_pipe(t_vm *vm, t_program *program)
{
	if (pipe(vm->pipedes) < 0)
	{
		ft_printf("pipe failed: %m\n");
		return ;
	}
	vm_exec(vm, program);
}
