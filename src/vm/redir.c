/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:06:13 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 22:26:21 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"

void	vm_redir_in(t_vm *vm, t_program *program)
{
	// todo
	(void)vm;
	program->pc += 4;
}

void	vm_redir_out(t_vm *vm, t_program *program)
{
	// todo
	(void)vm;
	program->pc += 4;
}
