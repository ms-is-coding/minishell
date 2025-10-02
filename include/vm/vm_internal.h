/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_internal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:33:47 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 16:35:21 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_INTERNAL_H
# define VM_INTERNAL_H

# include <stddef.h>
# include "vm.h"

typedef void	(*t_exec_handler)(t_vm *vm, t_program *program);

void	exec_wait(t_vm *vm, t_program *program);
void	exec_command(t_vm *vm, t_program *program);
void	exec_exec(t_vm *vm, t_program *program);
void	exec_arg(t_vm *vm, t_program *program);
void	exec_filename(t_vm *vm, t_program *program);
void	exec_pipe(t_vm *vm, t_program *program);
void	exec_background(t_vm *vm, t_program *program);
void	exec_redir_out(t_vm *vm, t_program *program);
void	exec_redir_in(t_vm *vm, t_program *program);
void	exec_jump(t_vm *vm, t_program *program);

#endif // VM_INTERNAL_H
