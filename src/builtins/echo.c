/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 22:10:09 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 00:00:57 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft_printf.h"

int	builtin_echo(t_shell *sh, int argc, char **argv)
{
	int	i;

	(void)sh;
	i = 0;
	while (++i < argc - 1)
	{
		ft_printf("%s ", argv[i]);
	}
	ft_printf("%s\n", argv[argc - 1]);
	return (0);
}
