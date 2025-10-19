/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:01:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/18 18:30:20 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include <errno.h>

int	builtin_exit(t_shell *sh, int argc, char **argv, char **envp)
{
	int		exit_code;
	
	(void)argv;
	(void)sh;
	(void)envp;
	exit_code = 0;
	if (argc > 2)
		return (builtin_error(ctx(argv[0], NULL), ERR_TOO_MANY_ARGS, 1));
	if (argc == 2)
		exit_code = ft_atoi_safe(argv[1]);
	if (errno == ERANGE)
		return (builtin_error(ctx(argv[0], argv[1]), ERR_NOT_NUMERIC, 255));
	write(1, "exit\n", 5);
	exit(exit_code);
	return (0);
}
