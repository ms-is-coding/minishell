/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:25:28 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/24 16:16:36 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "allocator/allocator.h"
# include "core/stdlib.h"
# include "vector/vector.h"
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
	t_vec			*pids;
	t_vec			*exit_codes;
	t_exec_frame	frame;

	t_vm_redir		redirs[MAX_REDIRS];

	int				pipe_fd[2];
	int				prev_fd;
	int				redir_count;
	int				last_exit_code;

	bool			active;
	bool			here_doc;
	bool			had_error;

	uint8_t			reserved[1];
}	t_vm;

t_result	vm_init(t_vm *vm);
void		vm_run(t_vm *vm, t_program *program);
void		vm_dispatch(t_vm *vm, int sig);

char		*find_exec(const char *arg, const char *env_path);

#endif // VM_H
