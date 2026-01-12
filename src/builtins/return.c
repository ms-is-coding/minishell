/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:26:30 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 17:10:54 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include <errno.h>
#include "core/string.h"

int	builtin_return(
	t_shell *sh,
	__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv,
	__attribute__((unused)) char **envp)
{
	int	exit_code;

	// FIX this is not working
	if (argc == 1)
		exit_code = (int64_t)vec_get(sh->vm.exit_codes, -1);
	if (argc > 2)
		return (builtin_error(ctx("return", NULL), ERR_TOO_MANY_ARGS, 2));
	if (argc == 2)
		exit_code = ft_atoi_safe(argv[1]);
	if (argc == 2 && (errno == ERANGE
			|| argv[1][ft_strspn(argv[1], "0123456789")] != '\0'))
		return (builtin_error(ctx("return", argv[1]), ERR_NOT_NUMERIC, 2));
	return (exit_code);
}
