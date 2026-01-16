/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:15:32 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 15:59:48 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

char	*ft_strcat(char *dst, const char *src)
{
	ft_stpcpy(dst + ft_strlen(dst), src);
	return (dst);
}
