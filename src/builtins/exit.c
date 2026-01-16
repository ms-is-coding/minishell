/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:01:02 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 16:35:39 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "builtins/builtins.h"
#include "core/string.h"
#include "shell.h"

/**
 * @brief Exits the shell.
 *
 * @param sh Pointer to the shell structure
 * @param argc Argument count
 * @param argv Argument vector
 * @param envp Environment variables (unused)
 * @return Exit code of the shell.

 */
int	builtin_exit(
	t_shell *sh,
	int argc,
	char **argv,
	__attribute__((unused)) char **envp)
{
	int		exit_code;
	char	*tmp;

	exit_code = 0;
	if (argc == 1)
	{
		sh->should_exit = true;
		return (sh->vm.last_exit_code);
	}
	exit_code = (int32_t)ft_atol_safe(argv[1]);
	tmp = argv[1];
	if (argv[1][0] == '+' || argv[1][0] == '-')
		tmp = argv[1] + 1;
	if (errno == ERANGE || tmp[ft_strspn(tmp, "0123456789")] != '\0')
		return (builtin_error(ctx("exit", argv[1]), ERR_NOT_NUMERIC, 2));
	if (argc > 2)
		return (builtin_error(ctx("exit", NULL), ERR_TOO_MANY_ARGS, 1));
	sh->should_exit = true;
	return (exit_code);
}
