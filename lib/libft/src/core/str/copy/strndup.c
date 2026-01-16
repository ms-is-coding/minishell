/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strndup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:09:04 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 15:59:27 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "core/string.h"

char	*ft_strndup(const char *s, const size_t n)
{
	size_t	i;
	char	*res;

	res = ft_malloc(sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	i = (size_t)-1;
	while (++i < n)
		res[i] = s[i];
	res[i] = 0;
	return (res);
}
