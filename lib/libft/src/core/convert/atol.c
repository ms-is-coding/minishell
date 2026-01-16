/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:37:47 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:05:37 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/ctype.h"

long	ft_atol(const char *s)
{
	long	value;
	int		sign;

	value = 0;
	sign = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
		sign = 44 - *s++;
	while (ft_isdigit(*s))
		value = value * 10 + *s++ - '0';
	return (sign * value);
}
