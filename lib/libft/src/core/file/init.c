/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:26:54 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:08:33 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"

__attribute__((__always_inline__))
static inline _Bool	_ft_file_has_data(t_file *file)
{
	return (file->curr < file->buf + file->len);
}

t_result	ft_file_init(t_file *file, int fd)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, file->buf, FILE_BUFFER_SIZE);
	if (bytes_read < 0)
		return (RESULT_READ_ERROR);
	file->fd = fd;
	file->len = (unsigned int)bytes_read;
	file->curr = file->buf;
	file->line = 1;
	file->eof = false;
	return (RESULT_OK);
}

_Bool	ft_file_eof(t_file *file)
{
	if (file->eof)
		return (true);
	if (file->curr == file->buf && file->len == 0)
		file->eof = true;
	return (file->eof);
}

t_result	ft_file_consume(t_file *file, char c, _Bool *found)
{
	t_result	r;

	if (ft_file_eof(file))
		return (RESULT_EOF);
	*found = false;
	if (_ft_file_has_data(file) && *file->curr == c)
	{
		r = _ft_file_advance(file);
		if (r != RESULT_OK)
			return (r);
		*found = true;
	}
	return (RESULT_OK);
}
