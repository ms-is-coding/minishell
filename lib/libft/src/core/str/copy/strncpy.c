/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:16:27 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 15:59:15 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

char	*ft_strncpy(char *dst, const char *src, size_t dsize)
{
	ft_stpncpy(dst, src, dsize);
	return (dst);
}
