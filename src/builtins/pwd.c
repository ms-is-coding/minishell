/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:20:05 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 18:36:59 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>

#include "builtins/builtins.h"
#include "core/string.h"

/**
 * @brief Prints the name of the current working directory.
 *
 * @param sh Pointer to the shell structure (unused)
 * @param argc Argument count (unused)
 * @param argv Argument vector (unused)
 * @param envp Environment pointer (unused)
 * @return Exit code of the command.
 */
int	builtin_pwd(
	__attribute__((unused)) t_shell *sh,
	__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv,
	__attribute__((unused)) char **envp)
{
	char	buf[PATH_MAX];
	size_t	len;

	if (!getcwd(buf, PATH_MAX))
		return (builtin_error(ctx("pwd", NULL), ERR_PERROR, 1));
	len = ft_strlen(buf);
	buf[len] = '\n';
	write(STDOUT_FILENO, buf, len + 1);
	ft_memset(buf, PATH_MAX, 0);
	return (0);
}
