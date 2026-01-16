/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnlen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:45:32 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 15:58:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

size_t	ft_strnlen(const char *s, size_t n)
{
	size_t	len;

	len = 0;
	while (n-- && s[len])
		len++;
	return (len);
}
