/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:40:57 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:21:06 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/printf_internal.h"

static void	_ft_printf_uint_internal(t_printf_parser *parser,
	uintmax_t n, int iters)
{
	if (!iters)
		return ;
	_ft_printf_uint_internal(parser, n / 10, iters - 1);
	_ft_printf_insert(parser, (char)(n % 10) + '0');
}

static int	_ft_printf_print_len(t_printf_parser *parser, uintmax_t n)
{
	const int	len = _ft_printf_uint_len(n);

	if (n == 0 && parser->prec == -1)
		return (1);
	if (parser->prec > len)
		return (parser->prec);
	return (len);
}

void	_ft_printf_uint(t_printf_parser *parser, uintmax_t n)
{
	const int	len = _ft_printf_print_len(parser, n);

	if (parser->prec >= 0)
		parser->flags &= ~PRINTF_FLAG_ZEROPAD;
	_ft_printf_padding(parser, len, PRINTF_START, PRINTF_NUMERIC);
	_ft_printf_uint_internal(parser, n, len);
	_ft_printf_padding(parser, len, PRINTF_END, PRINTF_NUMERIC);
}
