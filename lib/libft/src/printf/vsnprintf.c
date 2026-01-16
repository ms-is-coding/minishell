/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vsnprintf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:31:49 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:22:43 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdio.h"
#include "printf/printf_internal.h"

void	_ft_printf_invalid_format(t_printf_parser *p)
{
	p->prec = p->spec_pos;
	p->spec_buf[p->spec_pos] = 0;
	p->width = -1;
	_ft_printf_str(p, p->spec_buf);
}

int	ft_vsnprintf(char *dst, size_t size, const char *fmt, va_list ap)
{
	t_printf_parser	p;

	if (!fmt)
		return (-1);
	p.dst = dst;
	p.fmt = fmt;
	p.size = size;
	va_copy(p.ap, ap);
	_ft_printf_init_parser(&p);
	while (p.curr(&p))
	{
		_ft_printf_reset_parser(&p);
		while (p.curr(&p) && p.curr(&p) != '%')
			_ft_printf_insert(&p, *p.fmt++);
		if (!p.curr(&p))
			break ;
		p.next(&p);
		if (_ft_printf_handle_conv(&p))
			return (va_end(p.ap), -1);
	}
	if (p.pos < p.size)
		p.dst[p.pos] = 0;
	va_end(p.ap);
	return ((int)p.pos);
}
