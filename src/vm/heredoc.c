/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:52:21 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/26 15:27:34 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "util/help.h"
#include "vm/bytecode.h"
#include "vm/vm_internal.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include "core/string.h"
#include "core/stdio.h"

/**
 * @brief Inserts a redirection into the VM's redirection list.
 *
 * @param vm Pointer to the virtual machine
 * @param target_fd The target file descriptor
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
 * @brief Handles the heredoc input loop.
 *
 * @param vm Pointer to the virtual machine
 * @param filename The temporary file to store heredoc input
 * @param delim The delimiter string to end heredoc input
 */
static void	heredoc_loop(t_vm *vm, char *filename, char *delim)
{
	char	*line;
	int		fd;

	fd = open(filename, O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		ft_dprintf(2, "%s: %m\n", filename);
		vm->had_error = true;
	}
	while (1)
	{
		vm->here_doc = true;
		line = readline("> ");
		if (!line)
		{
			help_warn(HELP_HEREDOC_EOF);
			break ;
		}
		if (ft_strcmp(delim, line) == 0)
			break ;
		ft_dprintf(fd, "%s\n", line);
		free(line);
	}
	vm->here_doc = false;
}

static t_result	heredoc_open_file(char **filename)
{
	int	fd;
	int	i;

	i = 0;
	ft_snprintf(*filename, PATH_MAX, "/tmp/.msh_heredoc_%i", i);
	fd = open(*filename, O_CREAT | O_EXCL, 0600);
	while (fd == -1)
	{
		i++;
		if (i > 0x10000)
			return (RESULT_ERROR);
		ft_snprintf(*filename, PATH_MAX, "/tmp/.msh_heredoc_%i", i);
		fd = open(*filename, O_CREAT | O_EXCL, 0600);
	}
	close(fd);
	return (RESULT_OK);
}

/**
 * @brief Handles the heredoc opcode in the virtual machine.
 *
 * @param vm Pointer to the virtual machine
 * @param program Pointer to the program being executed
 */
void	vm_heredoc(t_vm *vm, t_program *program)
{
	int32_t		file_fd;
	int32_t		target_fd;
	uint16_t	len;
	char		*delim;
	char		filename[PATH_MAX];

	program->pc++;
	target_fd = program_get_i32(program);
	len = program_get_u16(program);
	if (target_fd == -1)
		target_fd = 0;
	delim = ft_strndup((char *)program->data + program->pc, len);
	if (heredoc_open_file((char **)&filename) != RESULT_OK)
	{
		ft_dprintf(2, "error: could not create heredoc\n");
		vm->had_error = true;
	}
	heredoc_loop(vm, filename, delim);
	ft_free(delim);
	file_fd = open(filename, O_RDONLY, 0600);
	redir_insert(vm, target_fd, file_fd);
	program->pc += len;
}
