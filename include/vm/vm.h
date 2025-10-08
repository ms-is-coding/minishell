/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:25:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 13:46:28 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "allocator/allocator.h"
# include "bytecode.h"
# include <stddef.h>

typedef struct s_exec_frame
{
	t_arena			*arena;
	char			**argv;
	int				argc;
	int				i;
}	t_exec_frame;

typedef struct s_vm
{
	void			*shell;
	t_allocator		*allocator;
	t_vector		pids;
	t_vector		exit_codes;
	t_exec_frame	frame;

	int				pipe_fd[2];
	int				prev_fd;
	int				file_fd;
	int				file_in;
	int				file_out;
}	t_vm;

int	vm_run(t_vm *vm, t_program *program);

#endif // VM_H
