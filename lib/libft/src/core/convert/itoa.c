/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:14:24 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:27:22 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "core/string.h"
#include "core/math.h"

char	*ft_itoa_unsafe(int n)
{
	static char	buf[12];
	int			i;

	i = ft_intlen(n);
	buf[i--] = 0;
	if (n < 0)
		buf[0] = '-';
	if (n == 0)
		buf[0] = '0';
	while (n)
	{
		buf[i--] = (char)ft_abs(n % 10) + '0';
		n /= 10;
	}
	return (buf);
}

char	*ft_itoa(int n)
{
	return (ft_strdup(ft_itoa_unsafe(n)));
}
