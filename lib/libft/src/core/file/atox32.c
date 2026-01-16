/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atox32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 08:39:18 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:08:49 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"

__attribute__((__always_inline__))
static inline _Bool	_ft_file_has_data(t_file *file)
{
	return (file->curr < file->buf + file->len);
}

static t_result	_ft_file_0x(t_file *file, _Bool optional)
{
	t_result	r;

	if (_ft_file_has_data(file) && *file->curr != '0')
	{
		if (optional)
			return (RESULT_OK);
		return (RESULT_INVAL);
	}
	r = _ft_file_advance(file);
	if (r != RESULT_OK)
		return (r);
	if (*file->curr == 'x' || *file->curr == 'X')
	{
		r = _ft_file_advance(file);
		if (r != RESULT_OK)
			return (r);
		return (RESULT_OK);
	}
	return (RESULT_INVAL);
}

t_result	ft_file_atox32(t_file *file, uint32_t *ret)
{
	t_result	r;

	if (ft_file_eof(file))
		return (RESULT_EOF);
	r = _ft_file_skip_whitespace(file);
	if (r != RESULT_OK)
		return (r);
	*ret = 0;
	r = _ft_file_0x(file, true);
	if (r != RESULT_OK)
		return (r);
	return (RESULT_OK);
}
