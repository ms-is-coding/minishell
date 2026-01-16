/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 08:45:16 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:06:55 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "core/string.h"
#include <stddef.h>

__attribute__((__always_inline__))
static inline _Bool	ft_file_can_advance(t_file *file)
{
	return (file->curr + 1 < file->buf + file->len);
}

t_result	_ft_file_refill(t_file *file)
{
	ssize_t	bytes_read;
	size_t	remaining;

	if (file->curr - 1 > file->buf)
	{
		remaining = (size_t)(file->len - (size_t)(file->curr - file->buf) - 1);
		ft_memmove(file->buf, file->curr, remaining);
		file->curr = file->buf;
		file->len = (unsigned int)remaining;
	}
	bytes_read = read(file->fd, file->buf + file->len,
			FILE_BUFFER_SIZE - file->len);
	if (bytes_read < 0)
		return (RESULT_READ_ERROR);
	if (bytes_read == 0)
	{
		file->eof = true;
		return (RESULT_EOF);
	}
	file->len += (unsigned int)bytes_read;
	return (RESULT_OK);
}

t_result	_ft_file_advance(t_file *file)
{
	t_result	result;

	if (!ft_file_can_advance(file))
	{
		result = _ft_file_refill(file);
		if (result != RESULT_OK)
			return (result);
	}
	if (*file->curr == '\n')
		file->line++;
	file->curr++;
	return (RESULT_OK);
}
