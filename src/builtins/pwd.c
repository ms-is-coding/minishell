/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:20:05 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/18 18:02:00 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>

#include "builtins/builtins.h"
#include "libft.h"
#include "env/env.h"

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
