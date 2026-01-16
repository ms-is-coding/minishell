/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 08:48:03 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:08:44 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "core/ctype.h"

__attribute__((__always_inline__))
static inline _Bool	_ft_file_has_data(t_file *file)
{
	return (file->curr < file->buf + file->len);
}

static t_result	temp(t_file *file, int32_t *ret_ptr, int sign)
{
	t_result	result;
	_Bool		had_digit;
	_Bool		overflow;
	int			digit;

	had_digit = false;
	overflow = false;
	while (_ft_file_has_data(file) && ft_isdigit(*file->curr))
	{
		digit = *file->curr - '0';
		if ((sign == -1 && *ret_ptr < (INT_MIN + digit) / 10)
			|| (sign == 1 && *ret_ptr > (INT_MAX - digit) / 10))
			overflow = true;
		*ret_ptr = *ret_ptr * 10 + sign * digit;
		result = _ft_file_advance(file);
		if (result == RESULT_READ_ERROR)
			return (result);
		had_digit = true;
	}
	if (!had_digit)
		return (RESULT_INVAL);
	if (overflow)
		return (RESULT_OVERFLOW);
	_ft_file_skip_whitespace(file);
	return (RESULT_OK);
}

t_result	ft_file_atoi32(t_file *file, int32_t *ret_ptr)
{
	int			sign;
	t_result	result;

	if (ft_file_eof(file))
		return (RESULT_EOF);
	*ret_ptr = 0;
	sign = 1;
	result = _ft_file_skip_whitespace(file);
	if (result != RESULT_OK)
		return (result);
	if (_ft_file_has_data(file) && *file->curr == '-')
	{
		sign = -1;
		result = _ft_file_advance(file);
		if (result != RESULT_OK)
			return (result);
	}
	else if (_ft_file_has_data(file) && *file->curr == '+')
		if (_ft_file_advance(file) != RESULT_OK)
			return (RESULT_ERROR);
	return (temp(file, ret_ptr, sign));
}
