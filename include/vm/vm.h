/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:25:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/17 02:18:15 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "allocator/allocator.h"
# include "bytecode.h"
# include "common.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

typedef struct s_exec_frame
{
	t_arena			*arena;
	char			**argv;
	int				argc;
	char			reserved[4];
}	t_exec_frame;

typedef struct s_vm_redir
{
	int32_t	target_fd;
	int32_t	file_fd;
}	t_vm_redir;

typedef struct s_vm
{
	void			*shell;
	t_allocator		*allocator;
	t_vector		pids;
	t_vector		exit_codes;
	t_exec_frame	frame;

	t_vm_redir		redirs[MAX_REDIRS];

	int				pipe_fd[2];
	int				prev_fd;
	int				redir_count;

	bool			active;
	bool			had_error;

	uint8_t			reserved[6];
}	t_vm;

void	vm_run(t_vm *vm, t_program *program);

#endif // VM_H
