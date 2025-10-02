/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:53:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 16:12:47 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_var(size_t idx, t_value val)
{
	(void)idx;
	ft_printf("%s\n", val.value.str);
}

int	builtin_env(t_shell *sh, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_vector_foreach(&sh->env.public, print_var);
	return (0);
}
