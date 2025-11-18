/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:52:21 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/18 18:17:54 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/help.h"
#include "vm/bytecode.h"
#include "vm/vm_internal.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>

static void	redir_insert(t_vm *vm, int32_t target_fd, int32_t file_fd)
{
	int	i;

	i = vm->redir_count++;
	vm->redirs[i].target_fd = target_fd;
	vm->redirs[i].file_fd = file_fd;
}

static void	heredoc_loop(t_vm *vm, char *filename, char *delim)
{
	char	*line;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
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
	}
	vm->here_doc = false;
}

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
	ft_snprintf(filename, PATH_MAX, "/tmp/.msh_heredoc_%i", vm->redir_count);
	heredoc_loop(vm, filename, delim);
	free(delim);
	file_fd = open(filename, O_RDONLY, 0600);
	if (file_fd == -1)
	{
		ft_dprintf(2, "%s: %m\n", filename);
		vm->had_error = true;
	}
	redir_insert(vm, target_fd, file_fd);
	program->pc += len;
}
