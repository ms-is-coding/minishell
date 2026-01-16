/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:48:27 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:24:26 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/math.h"
#include <stdarg.h>

int	ft_nmin(int n, ...)
{
	va_list	args;
	int		min;
	int		temp;

	va_start(args, n);
	min = va_arg(args, int);
	while (--n)
	{
		temp = va_arg(args, int);
		if (temp < min)
			min = temp;
	}
	va_end(args);
	return (min);
}
