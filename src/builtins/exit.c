/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:01:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/18 18:00:31 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "builtins/builtins.h"
#include "libft.h"

int	builtin_exit(
	__attribute__((unused)) t_shell *sh,
	int argc,
	__attribute__((unused)) char **argv,
	__attribute__((unused)) char **envp)
{
	int		exit_code;

	exit_code = 0;
	// FIX this is still not working
	if (argc == 1)
		exit_code = ft_vector_at(&sh->vm.exit_codes, -1).value.i32;
	if (argc > 2)
		return (builtin_error(ctx("exit", NULL), ERR_TOO_MANY_ARGS, 2));
	if (argc == 2)
		exit_code = ft_atoi_safe(argv[1]);
	if (argc == 2 && (errno == ERANGE
		|| argv[1][ft_strspn(argv[1], "0123456789")] != '\0'))
		return (builtin_error(ctx("exit", argv[1]), ERR_NOT_NUMERIC, 2));
	if (1) // need a check for interactive mode
		write(2, "exit\n", 5);
	exit(exit_code);
	return (exit_code);
}
