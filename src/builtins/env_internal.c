/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_internal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:08:12 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/11/03 13:35:50 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>

#include "libft.h"

#define FLAG_I	1

bool	is_valid_assignment(const char *str)
{
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	if (*str == '=')
		return (true);
	return (false);
}

int	is_existing_var(char **envp, const char *assignment)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (assignment[len] && assignment[len] != '=')
		len++;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], assignment, len) == 0
			&& (envp[i][len] == '=' || envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	print_env(char **envp)
{
	size_t	len;

	while (*envp)
	{
		len = ft_strlen(*envp);
		(*envp)[len] = '\n';
		write(1, *envp, len + 1);
		envp++;
	}
}

size_t	get_env_size(char **argv, char **envp, char flags)
{
	size_t	count;
	size_t	i;

	count = 0;
	if (!(flags & FLAG_I) && envp)
	{
		while (envp[count])
			count++;
	}
	i = 0;
	while (argv[i] && is_valid_assignment(argv[i]))
	{
		if (is_existing_var(envp, argv[i]) == -1)
			count++;
		i++;
	}
	return (count);
}
