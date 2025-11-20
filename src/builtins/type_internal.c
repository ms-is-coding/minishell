/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:41:11 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/11/20 11:43:08 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins/type_internal.h"
#include "libft.h"

#define MAX_LEN	126 //How to handle path_max ?

//need to handle NULL, need to also norm
void	type_info(const char *name, const char *path, char type, char flags)
{
	char	buf[MAX_LEN + 2];
	size_t	len;

	ft_memset(buf, 0, MAX_LEN + 2);
	if (flags & FLAG_T)
	{
		if (type & TYPE_EXEC)
			len = ft_strlcpy(buf, "file", MAX_LEN);
		else if (flags & FLAG_PP)
			return ;
		else if (type & TYPE_BUILTIN)
			len = ft_strlcpy(buf, "builtin", MAX_LEN);
		else
			len = ft_strlcpy(buf, "unknown", MAX_LEN);
	}
	else
	{
		if (flags & (FLAG_P | FLAG_PP))
		{
			if (!(type & TYPE_EXEC))
				return ;
			len = ft_strlcpy(buf, path, MAX_LEN);
		}
		else
		{
			ft_strlcpy(buf, name, MAX_LEN);
			ft_strlcat(buf, " is ", MAX_LEN);
			if (type & TYPE_BUILTIN)
				len = ft_strlcat(buf, "a shell builtin", MAX_LEN);
			else if (type & TYPE_EXEC)
				len = ft_strlcat(buf, path, MAX_LEN);
			else
				len = ft_strlcat(buf, "unknown", MAX_LEN);
		}
	}
	buf[len] = '\n';
	write(STDOUT_FILENO, buf, len + 1);
}
