/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 23:51:08 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/23 17:35:02 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/printf_internal.h"

int	_ft_printf_int_len(intmax_t n)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

int	_ft_printf_uint_len(uintmax_t n)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

intmax_t	_ft_printf_abs(intmax_t n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	_ft_printf_abs_char(signed char c)
{
	if (c < 0)
		return ((signed char)-c);
	return (c);
}

void	_ft_printf_char(t_printf_parser *p, char c)
{
	_ft_printf_padding(p, 1, PRINTF_START, PRINTF_OTHER);
	_ft_printf_insert(p, c);
	_ft_printf_padding(p, 1, PRINTF_END, PRINTF_OTHER);
}
