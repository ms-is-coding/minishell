/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:17:46 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:20:54 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/printf_internal.h"
#include <errno.h>
#include <string.h>

static int	_ft_can_print(t_printf_parser *p)
{
	if (p->prec == -1)
		return (1);
	if (p->prec--)
		return (1);
	return (0);
}

void	_ft_printf_str(t_printf_parser *p, const char *s)
{
	size_t	len;
	size_t	i;

	if (!s && (p->prec < 0 || p->prec > 5))
	{
		_ft_printf_str(p, "(null)");
		return ;
	}
	else if (!s)
	{
		_ft_printf_str(p, "");
		return ;
	}
	len = _ft_printf_strnlen(s, (size_t)p->prec);
	i = 0;
	_ft_printf_padding(p, (int)len, PRINTF_START, PRINTF_OTHER);
	while (i < len && s[i] && _ft_can_print(p))
		_ft_printf_insert(p, s[i++]);
	_ft_printf_padding(p, (int)len, PRINTF_END, PRINTF_OTHER);
}

void	_ft_printf_strerror(t_printf_parser *p)
{
	if (p->flags & PRINTF_FLAG_ALTERNATE)
	{
		_ft_printf_str(p, _ft_str_errorname(errno));
		return ;
	}
	_ft_printf_str(p, strerror(errno));
}
