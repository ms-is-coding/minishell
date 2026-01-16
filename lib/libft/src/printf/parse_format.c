/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:17:29 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:20:21 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/printf_internal.h"
#include <errno.h>
#include <limits.h>

static void	_ft_printf_error(int error)
{
	errno = error;
}

int	_ft_printf_parse_precision(t_printf_parser *p)
{
	int	overflow;

	overflow = 0;
	p->prec = 0;
	if (p->match(p, '*'))
	{
		p->prec = va_arg(p->ap, int);
		return (0);
	}
	while (_ft_printf_isdigit(p->curr(p)) && !overflow)
	{
		p->prec = p->prec * 10 + p->curr(p) - '0';
		if (_ft_printf_isdigit(p->next(p)) && (p->prec > INT_MAX / 10
				|| (p->prec == INT_MAX / 10 && p->curr(p) > '7')))
			overflow = 1;
	}
	if (overflow)
	{
		_ft_printf_error(EOVERFLOW);
		return (1);
	}
	return (0);
}

static	void	_ft_printf_patch_width(t_printf_parser *p)
{
	if (p->width >= 0)
		return ;
	p->width = -p->width;
	p->flags |= PRINTF_FLAG_LEFTADJ;
}

int	_ft_printf_parse_width(t_printf_parser *p)
{
	int	overflow;

	overflow = 0;
	p->width = 0;
	if (p->match(p, '*'))
	{
		p->width = va_arg(p->ap, int);
		_ft_printf_patch_width(p);
		return (0);
	}
	while (_ft_printf_isdigit(p->curr(p)) && !overflow)
	{
		p->width = p->width * 10 + p->next(p) - '0';
		if (_ft_printf_isdigit(p->curr(p)) && (p->width > INT_MAX / 10
				|| (p->width == INT_MAX / 10 && *p->fmt > '7')))
			overflow = 1;
	}
	if (overflow)
	{
		_ft_printf_error(EOVERFLOW);
		return (1);
	}
	return (0);
}
