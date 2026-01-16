/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:01:30 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 20:31:49 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/prompt.h"
#include "ansi.h"
#include "common.h"
#include "core/stdio.h"
#include "core/stdlib.h"
#include "core/string.h"
#include "shell.h"
#include "util/signals.h"
#include <stdio.h>
#include <sys/types.h>
#include <termios.h>

typedef struct s_prompt
{
	char	buf[PROMPT_SIZE];
	size_t	size;
	size_t	len;
}	t_prompt;

/**
 * @brief Custom prompt printf that avoids segfaults
 *
 * @param p pointer to the prompt structure
 * @param fmt format string (identical to printf)
 */
static void	prompt_printf(t_prompt *p, const char *fmt, ...)
{
	va_list	ap;
	int		n;

	if (p->len >= p->size)
		return ;
	va_start(ap, fmt);
	n = ft_vsnprintf(p->buf + p->len, p->size - p->len, fmt, ap);
	va_end(ap);
	if (n < 0)
		return ;
	if ((size_t)n >= p->size - p->len)
		p->len = p->size - 1;
	else
		p->len += (size_t)n;
}

/**
 * @brief Constructs a shortened exit codes portion of the prompt (up to 16)
 *
 * @param sh Pointer to the shell structure
 * @param p Pointer to the prompt structure
 */
static void	prompt_exit_codes_short(t_shell *sh, t_prompt *p)
{
	const char	*color;
	const char	*killsig;
	int			code;
	int			i;

	color = ANSI_RED;
	if (vec_get(sh->vm.exit_codes, -1) == 0)
		color = ANSI_GREEN;
	i = (int)vec_length(sh->vm.exit_codes) - 16;
	prompt_printf(p, "%s...|", color);
	while (++i < (int64_t)vec_length(sh->vm.exit_codes) - 1)
	{
		code = (int32_t)(int64_t)vec_get(sh->vm.exit_codes, i);
		killsig = kill_signals(code - 128);
		(void)(!killsig && (killsig = ft_itoa_unsafe(code)));
		prompt_printf(p, "%s|", killsig);
	}
	code = (int32_t)(int64_t)vec_get(sh->vm.exit_codes, -1);
	killsig = kill_signals(code - 128);
	(void)(!killsig && (killsig = ft_itoa_unsafe(code)));
	prompt_printf(p, "%s ", killsig);
}

/**
 * @brief Constructs the exit codes portion of the prompt.
 *
 * @param sh Pointer to the shell structure
 * @param p Pointer to the prompt structure
 */
static void	prompt_exit_codes(t_shell *sh, t_prompt *p)
{
	const char	*color;
	const char	*killsig;
	int			code;
	int			i;

	color = ANSI_RED;
	if (vec_get(sh->vm.exit_codes, -1) == 0)
		color = ANSI_GREEN;
	if (vec_length(sh->vm.exit_codes) > 16)
		return (prompt_exit_codes_short(sh, p));
	i = -1;
	prompt_printf(p, "%s", color);
	while (++i < (int64_t)vec_length(sh->vm.exit_codes) - 1)
	{
		code = (int32_t)(int64_t)vec_get(sh->vm.exit_codes, i);
		killsig = kill_signals(code - 128);
		(void)(!killsig && (killsig = ft_itoa_unsafe(code)));
		prompt_printf(p, "%s|", killsig);
	}
	code = (int32_t)(int64_t)vec_get(sh->vm.exit_codes, -1);
	killsig = kill_signals(code - 128);
	(void)(!killsig && (killsig = ft_itoa_unsafe(code)));
	prompt_printf(p, "%s ", killsig);
}

/**
 * @brief Constructs the current working directory portion of the prompt.
 *
 * @param sh Pointer to the shell structure
 * @param p Pointer to the prompt structure
 */
static void	prompt_pwd(t_shell *sh, t_prompt *p)
{
	const char	*home;
	char		pwd[PATH_MAX];
	const char	*tmp;

	tmp = env_get(&sh->env, "PWD");
	if (tmp)
		ft_strlcpy(pwd, tmp, PATH_MAX);
	else if (!getcwd(pwd, PATH_MAX))
		ft_strlcpy(pwd, "(unknown)", PATH_MAX);
	home = env_get(&sh->env, "HOME");
	if (ft_strstr(pwd, home))
		ft_snprintf(pwd, PATH_MAX, "~%s", pwd + ft_strlen(home));
	prompt_printf(p, ANSI_BLUE "[%s] ", pwd);
}

/**
 * @brief Constructs the prompt and returns it
 *
 * @param sh Pointer to the shell structure
 */
const char	*generate_prompt(t_shell *sh)
{
	static t_prompt	p;

	p.len = 0;
	p.buf[0] = '\0';
	p.size = PROMPT_SIZE;
	prompt_pwd(sh, &p);
	if (p.len > PROMPT_SIZE - 48)
	{
		p.len = PROMPT_SIZE - 48;
		prompt_printf(&p, "...] ");
	}
	prompt_exit_codes(sh, &p);
	if (p.len > PROMPT_SIZE - 12)
	{
		p.len = PROMPT_SIZE - 12;
		prompt_printf(&p, "... ");
	}
	prompt_printf(&p, ANSI_RESET "$ ");
	return (p.buf);
}
