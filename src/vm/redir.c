/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:06:13 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 14:03:32 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"
#include "vm/bytecode.h"
#include "vm/vm_internal.h"
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include "core/stdio.h"

/**
 * @brief Inserts a redirection entry into the VM's redirection list.
 *
 * @param vm Pointer to the virtual machine
 * @param target_fd The target file descriptor to redirect
 * @param file_fd The file descriptor to redirect to
 */
static void	redir_insert(t_vm *vm, int32_t target_fd, int32_t file_fd)
{
	int	i;

	i = vm->redir_count++;
	vm->redirs[i].target_fd = target_fd;
	vm->redirs[i].file_fd = file_fd;
}

/**
 * @brief Handles input redirection in the virtual machine.
 *
 * @param vm Pointer to the virtual machine
 * @param program Pointer to the program being executed
 */
void	vm_redir_in(t_vm *vm, t_program *program)
{
	int32_t		file_fd;
	int32_t		target_fd;
	uint16_t	len;
	char		*filename;

	program->pc++;
	target_fd = program_get_i32(program);
	len = program_get_u16(program);
	if (target_fd == -1)
		target_fd = 0;
	filename = ft_strndup((char *)program->data + program->pc, len);
	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
	{
		ft_dprintf(2, "%s: %m\n", filename);
		vm->had_error = true;
	}
	ft_free(filename);
	redir_insert(vm, target_fd, file_fd);
	program->pc += len;
}

/**
 * @brief Handles output redirection in the virtual machine.
 *
 * @param vm Pointer to the virtual machine
 * @param program Pointer to the program being executed
 */
void	vm_redir_out(t_vm *vm, t_program *program)
{
	t_opcode	opcode;
	int32_t		file_fd;
	int32_t		target_fd;
	uint16_t	len;
	char		*filename;

	opcode = program->data[program->pc++];
	target_fd = program_get_i32(program);
	len = program_get_u16(program);
	if (target_fd == -1)
		target_fd = 1;
	filename = ft_strndup((char *)program->data + program->pc, len);
	if (opcode & REDIR_APPEND_BIT)
		file_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
	{
		ft_dprintf(2, "%s: %m\n", filename);
		vm->had_error = true;
	}
	ft_free(filename);
	redir_insert(vm, target_fd, file_fd);
	program->pc += len;
}

/**
 * @brief Dummy handler for redirection opcodes that skips over the data.
 *
 * @param vm Pointer to the virtual machine
 * @param program Pointer to the program being executed
 */
void	vm_redir_dummy(t_vm *vm, t_program *program)
{
	uint16_t	len;

	(void)vm;
	program->pc++;
	program_get_i32(program);
	len = program_get_u16(program);
	program->pc += len;
}
