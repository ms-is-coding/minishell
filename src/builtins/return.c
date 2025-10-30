/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:26:30 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/23 19:29:22 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include <errno.h>

int	builtin_return(t_shell *sh, int argc, char **argv, char **envp)
{
	int	exit_code;

	(void)sh;
	(void)argc;
	(void)argv;
	(void)envp;
	// FIX this is not working
	if (argc == 1)
		exit_code = ft_vector_at(&sh->vm.exit_codes, -1).value.i32;
	if (argc > 2)
		return (builtin_error(ctx(argv[0], NULL), ERR_TOO_MANY_ARGS, 2));
	if (argc == 2)
		exit_code = ft_atoi_safe(argv[1]);
	if (argc == 2 && (errno == ERANGE
		|| argv[1][ft_strspn(argv[1], "0123456789")] != '\0'))
		return (builtin_error(ctx(argv[0], argv[1]), ERR_NOT_NUMERIC, 2));
	return (exit_code);
}
