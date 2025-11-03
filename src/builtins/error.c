/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:35:31 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/11/03 12:05:26 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

#include "builtins/builtins.h"
#include "libft.h"

#define THREE_DOT	"..."
#define MSG_LIMIT	128
#define BLTN_LIMIT	16
#define SUBJ_LIMIT	16
#define INFO_LIMIT	92

static const char	*get_error_info(t_error err)
{
	static const char	*info[] = {
	[ERR_NONE] = ": Success",
	[ERR_INVALID_NAME] = ": invalid name",
	[ERR_TOO_MANY_ARGS] = ": too many arguments",
	[ERR_INVALID_OPT] = ": invalid option",
	[ERR_INVALID_ALIAS] = ": usage: alias [-p] [name[=value] ... ]",
	[ERR_INVALID_UNALIAS] = ": usage: unalias [-a] name [name ...]",
	[ERR_INVALID_ID] = ": not a valid identifier",
	[ERR_NO_HOME] = ": HOME not found",
	[ERR_NO_OLDPWD] = ": OLDPWD not found",
	[ERR_BAD_SET] = ": could not set variable",
	[ERR_READONLY_UNSET] = ": cannot unset: readonly variable",
	[ERR_BAD_RM] = ": could not remove variable",
	[ERR_TOO_LONG] = ": path too long",
	[ERR_NOT_NUMERIC] = ": numeric argument required",
	[ERR_404] = ": not found",
	[ERR_NO_FILE] = ": no such file",
	[ERR_NO_PERM] = ": Permission denied",
	[ERR_PERROR] = ": system error",
	[ERR_UNKNOWN] = ": unknown error"
	};

	if (err < 0 || err >= ERR_COUNT)
		return (info[ERR_UNKNOWN]);
	return (info[err]);
}

static size_t	get_context(char *buf, t_context ctx)
{
	size_t	i;
	size_t	copied;

	i = 0;
	copied = ft_strlcpy(buf, ctx.builtin, BLTN_LIMIT + 1);
	if (i >= BLTN_LIMIT)
		i = BLTN_LIMIT + ft_strlcpy(&buf[BLTN_LIMIT], THREE_DOT, 4);
	else
		i += copied;
	if (ctx.subject)
	{
		buf[i++] = ':';
		buf[i++] = ' ';
		copied = ft_strlcpy(&buf[i], ctx.subject, SUBJ_LIMIT + 1);
		if (copied > SUBJ_LIMIT)
			i = SUBJ_LIMIT + ft_strlcpy(&buf[SUBJ_LIMIT], THREE_DOT, 4);
		else
			i += copied;
	}
	return (i);
}

static size_t	get_error_message(char *buf, t_error err, t_context ctx)
{
	size_t	i;
	size_t	copied;

	i = get_context(buf, ctx);
	copied = ft_strlcpy(&buf[i], get_error_info(err), INFO_LIMIT + 1);
	if (copied > INFO_LIMIT)
		i += INFO_LIMIT + ft_strlcpy(&buf[i + INFO_LIMIT], THREE_DOT, 4);
	else
		i += copied;
	buf[i++] = '\n';
	buf[i] = '\0';
	return (i);
}

t_context	ctx(const char *builtin, const char *subject)
{
	t_context	ctx;

	if (!builtin || !*builtin)
		builtin = "unknown";
	ctx.builtin = builtin;
	if (!subject)
		subject = NULL;
	ctx.subject = subject;
	return (ctx);
}

int	builtin_error(t_context ctx, t_error err, int int_code)
{
	char	msg[MSG_LIMIT];
	size_t	size;

	if (err == ERR_NONE)
		return (0);
	if (err == ERR_PERROR)
	{
		get_context(msg, ctx);
		perror(msg);
	}
	else
	{
		size = get_error_message(msg, err, ctx);
		write(2, msg, size);
	}
	return (int_code);
}
