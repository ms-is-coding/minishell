/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:35:31 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/07 12:58:05 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

#include "builtins.h"
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
		[ERR_NOT_FOUND] = ": not found",
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
	buf[i++] = ':';
	copied = ft_strlcpy(&buf[i], ctx.subject, SUBJ_LIMIT + 1);
	if (copied > SUBJ_LIMIT)
		i = SUBJ_LIMIT + ft_strlcpy(&buf[i], THREE_DOT, 4);
	else
		i += copied;
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
	if (!subject || !*subject)
		subject = "";
	ctx.subject = subject;
	return (ctx);
}

void	builtin_error(t_context ctx, t_error err)
{
	char	msg[MSG_LIMIT];
	size_t	size;

	if (err == ERR_NONE)
		return ;
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
}
