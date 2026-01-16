/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:09:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:19:41 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/printf_internal.h"
#include <limits.h>
#include <stdarg.h>

static int	_ft_printf_set_mod(t_printf_parser *p, const char *s, int mod)
{
	int	i;

	i = 0;
	while (s[i] && p->fmt[i] == s[i])
		i++;
	if (s[i] == '\0')
	{
		p->len_mod = mod;
		p->fmt += i;
		return (1);
	}
	return (0);
}

static void	_ft_printf_len_mod(t_printf_parser *p)
{
	if (_ft_printf_set_mod(p, "hh", PRINTF_LEN_HH))
		return ;
	if (_ft_printf_set_mod(p, "ll", PRINTF_LEN_LL))
		return ;
	if (_ft_printf_set_mod(p, "L", PRINTF_LEN_LL))
		return ;
	if (_ft_printf_set_mod(p, "q", PRINTF_LEN_LL))
		return ;
	if (_ft_printf_set_mod(p, "h", PRINTF_LEN_H))
		return ;
	if (_ft_printf_set_mod(p, "l", PRINTF_LEN_L))
		return ;
	if (_ft_printf_set_mod(p, "j", PRINTF_LEN_J))
		return ;
	if (_ft_printf_set_mod(p, "z", PRINTF_LEN_Z))
		return ;
	if (_ft_printf_set_mod(p, "Z", PRINTF_LEN_Z))
		return ;
	if (_ft_printf_set_mod(p, "t", PRINTF_LEN_T))
		return ;
}

static void	_ft_printf_conversion(t_printf_parser *p)
{
	if (p->match(p, 'n'))
		_ft_printf_save_pos(p, va_arg(p->ap, void *));
	else if (p->match(p, 's'))
		_ft_printf_str(p, va_arg(p->ap, const char *));
	else if (p->match(p, '%'))
		_ft_printf_insert(p, '%');
	else if (p->match(p, 'c'))
		_ft_printf_char(p, (char)va_arg(p->ap, int));
	else if (p->match(p, 'i') || p->match(p, 'd'))
		_ft_printf_handle_int(p);
	else if (p->match(p, 'u'))
		_ft_printf_handle_uint(p);
	else if (p->match(p, 'm'))
		_ft_printf_strerror(p);
	else if (p->match(p, 'p'))
		_ft_printf_pointer(p, va_arg(p->ap, const void *));
	else if (p->match(p, 'x'))
		_ft_printf_handle_hex(p, 0x20);
	else if (p->match(p, 'X'))
		_ft_printf_handle_hex(p, 0);
	else
		_ft_printf_invalid_format(p);
}

int	_ft_printf_handle_conv(t_printf_parser *p)
{
	while (_ft_printf_strchr("#0- +", p->curr(p)))
		_ft_printf_parse_flags(p);
	if (_ft_printf_parse_width(p))
		return (1);
	if (p->match(p, '.') && _ft_printf_parse_precision(p))
		return (1);
	_ft_printf_len_mod(p);
	_ft_printf_conversion(p);
	return (0);
}
