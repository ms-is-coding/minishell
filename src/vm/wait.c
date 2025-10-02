/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:26:41 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 22:28:12 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"
#include <sys/wait.h>

void	vm_wait(t_vm *vm, t_program *program)
{
	int	i;
	int	stat;

	i = -1;
	(void)program;
	while (++i < (int)vm->pids.length)
	{
		waitpid(ft_vector_at(&vm->pids, i).value.i32, &stat, 0);
	}
}
