/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:25:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 16:26:28 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "bytecode.h"
# include <stddef.h>

typedef struct s_vm
{
	t_vector	pids;
	t_vector	exit_codes;
	int			pipedes[2];
	int			prev_fd;

	char		reserved[4];
}	t_vm;

int	vm_run(t_vm *vm, t_program *program);

#endif // VM_H
