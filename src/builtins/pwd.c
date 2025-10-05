/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:20:05 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 23:56:50 by smamalig         ###   ########.fr       */
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
	(void)argv;
	ft_vector_foreach(&sh->environ.public, print_pwd);
	return (0);
}
