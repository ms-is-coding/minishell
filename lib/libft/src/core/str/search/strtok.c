/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:49:26 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 15:57:21 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/string.h"

char	*ft_strtok(char *s, const char *delim)
{
	static char	*saveptr = NULL;
	char		*token;

	if (!s)
		s = saveptr;
	if (!s)
		return (NULL);
	s += ft_strspn(s, delim);
	if (!*s)
	{
		saveptr = s;
		return (NULL);
	}
	token = s;
	s = ft_strpbrk(token, delim);
	if (s == NULL)
		saveptr = ft_strchr(token, '\0');
	else
	{
		*s = '\0';
		saveptr = s + 1;
	}
	return (token);
}
