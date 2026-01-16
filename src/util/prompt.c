/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:01:30 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 17:34:15 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/prompt.h"
#include "ansi.h"
#include "core/stdio.h"
#include "core/stdlib.h"
#include "core/string.h"
#include "shell.h"
#include "util/signals.h"
#include <stdio.h>
#include <sys/types.h>
#include <termios.h>

/**
 * @brief Constructs the exit codes portion of the prompt.
 *
 * @param sh Pointer to the shell structure
 * @param prompt Buffer to store the constructed prompt
 */
void	prompt_exit_codes(t_shell *sh, char *prompt, ssize_t *len)
{
	const char	*color;
	const char	*killsig;
	int			code;
	int			i;

	color = ANSI_RED;
	if (vec_get(sh->vm.exit_codes, -1) == 0)
		color = ANSI_GREEN;
	i = -1;
	while (++i < (int64_t)vec_length(sh->vm.exit_codes) - 1)
	{
		code = (int32_t)(int64_t)vec_get(sh->vm.exit_codes, i);
		killsig = kill_signals(code - 128);
		(void)(!killsig && (killsig = ft_itoa_unsafe(code)));
		*len += ft_snprintf(prompt + *len, (size_t)(PROMPT_SIZE - *len),
				"%s%s|", color, killsig);
	}
	code = (int32_t)(int64_t)vec_get(sh->vm.exit_codes, -1);
	killsig = kill_signals(code - 128);
	(void)(!killsig && (killsig = ft_itoa_unsafe(code)));
	*len += ft_snprintf(prompt + *len, (size_t)(PROMPT_SIZE - *len),
			"%s%s " ANSI_RESET, color, killsig);
}

/**
 * @brief Constructs the current working directory portion of the prompt.
 *
 * @param sh Pointer to the shell structure
 * @param prompt Buffer to store the constructed prompt
 */
void	prompt_pwd(t_shell *sh, char *prompt, ssize_t *len)
{
	const char	*home;
	char		pwd[PATH_MAX];
	const char	*tmp;

	tmp = env_get(&sh->env, "PWD");
	if (tmp)
		ft_strlcpy(pwd, tmp, PATH_MAX);
	else
		getcwd(pwd, PATH_MAX);
	home = env_get(&sh->env, "HOME");
	if (ft_strstr(pwd, home))
		ft_snprintf(pwd, PATH_MAX, "~%s", pwd + ft_strlen(home));
	*len += ft_snprintf(prompt + *len, (size_t)(PROMPT_SIZE - *len),
			ANSI_BLUE "[%s] " ANSI_RESET, pwd);
}
