/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:33:19 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/03 16:06:45 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"
#include <fcntl.h>
#include <unistd.h>

void	vm_filename(t_vm *vm, t_program *program)
{
	size_t	len;
	char	*filename;

	// todo
	len = program->data[++program->pc];
	filename = ft_strndup((char *)program->data + program->pc + 1, len);
	if (!filename)
		return ;
	vm->file_fd = open(filename, O_RDWR | O_CREAT, 0644);
	ft_printf("Opening %s: %m\n", filename);
	free(filename);
	program->pc += len;
}
