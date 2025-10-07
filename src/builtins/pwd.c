/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:20:05 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 12:27:22 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

static void	print_pwd(size_t idx, t_value val)
{
	(void)idx;
	if (ft_strncmp("PWD=", val.value.str, 4) != 0)
		return ;
	ft_printf("%s\n", val.value.str + 4);
}

int	builtin_pwd(t_shell *sh, int argc, char **argv)
{
	(void)argc;
	(void)argv; //to beautify
	ft_vector_foreach(&sh->env.public, print_pwd);
	return (0);
}
