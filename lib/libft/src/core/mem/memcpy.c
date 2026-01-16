/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:15:51 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:01:22 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	ft_mempcpy(dst, src, n);
	return (dst);
}
