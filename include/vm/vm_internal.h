/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_internal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:33:47 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/05 20:34:49 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_INTERNAL_H
# define VM_INTERNAL_H

# include <stddef.h>
# include "vm.h"

typedef void	(*t_exec_handler)(t_vm *vm, t_program *program);

void	vm_dispatch(t_vm *vm, int sig);

void	vm_wait(t_vm *vm, t_program *program);
void	vm_command(t_vm *vm, t_program *program);
void	vm_exec(t_vm *vm, t_program *program);
void	vm_arg(t_vm *vm, t_program *program);
void	vm_filename(t_vm *vm, t_program *program);
void	vm_pipe(t_vm *vm, t_program *program);
void	vm_background(t_vm *vm, t_program *program);
void	vm_redir_out(t_vm *vm, t_program *program);
void	vm_redir_in(t_vm *vm, t_program *program);
void	vm_jnz(t_vm *vm, t_program *program);
void	vm_jz(t_vm *vm, t_program *program);

#endif // VM_INTERNAL_H
