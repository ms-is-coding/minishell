/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmax.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:35:50 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:24:22 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/math.h"
#include <stdarg.h>

int	ft_nmax(int n, ...)
{
	va_list	args;
	int		max;
	int		temp;

	va_start(args, n);
	max = va_arg(args, int);
	while (--n)
	{
		temp = va_arg(args, int);
		if (temp > max)
			max = temp;
	}
	va_end(args);
	return (max);
}
