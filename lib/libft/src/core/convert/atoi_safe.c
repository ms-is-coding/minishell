/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_safe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:13:22 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:05:32 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/ctype.h"
#include <errno.h>
#include <limits.h>

#define UPPER_DIGIT 7
#define LOWER_DIGIT 8

int	ft_atoi_safe(const char *s)
{
	int	value;
	int	sign;

	value = 0;
	sign = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
		sign = 44 - *s++;
	while (ft_isdigit(*s) && errno != ERANGE)
	{
		value = value * 10 + *s++ - '0';
		if (ft_isdigit(*s) && (value > INT_MAX / 10
				|| (sign == 1 && value == INT_MAX / 10
					&& *s - '0' > UPPER_DIGIT)
				|| (sign == -1 && value == INT_MAX / 10
					&& *s - '0' > LOWER_DIGIT)))
			errno = ERANGE;
	}
	if (errno == ERANGE && sign == 1)
		return (INT_MAX);
	else if (errno == ERANGE)
		return (INT_MIN);
	return (sign * value);
}
