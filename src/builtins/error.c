/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:35:31 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/15 12:58:31 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

#include "builtins/builtins.h"
#include "core/string.h"

#define THREE_DOT	"..."
#define MSG_LIMIT	128
#define BLTN_LIMIT	16
#define SUBJ_LIMIT	16
#define INFO_LIMIT	92

/**
 * @brief Retrieves the error information string corresponding to the error
 * code.
 *
 * @param err The error code
 * @return The error information string.
 */
static const char	*get_error_info(t_error err)
{
	static const char	*info[] = {
	[ERR_NONE] = ": Success",
	[ERR_TOO_MANY_ARGS] = ": too many arguments",
	[ERR_INVALID_OPT] = ": invalid option",
	[ERR_INVALID_ID] = ": not a valid identifier",
	[ERR_NO_HOME] = ": HOME not found",
	[ERR_NO_OLDPWD] = ": OLDPWD not found",
	[ERR_PREV_DIR] = ": roll-backed to previous DIR, which does not exist",
	[ERR_CURR_DIR] = ": current DIR does not exist",
	[ERR_BAD_SET] = ": could not set variable",
	[ERR_READONLY] = ": cannot unset, readonly variable",
	[ERR_NOT_NUMERIC] = ": numeric argument required",
	[ERR_404] = ": not found",
	[ERR_NO_PERM] = ": Permission denied",
	[ERR_HELP_NOT_FOUND] = ": help topic not found",
	[ERR_HELP_DIRTY] = ": Please mind your language when asking for help.",
	[ERR_HELP_EXCESS] = ": Are you begging for help?",
	[ERR_ALLOC] = ": internal memory allocation failed",
	[ERR_PERROR] = ": system error",
	[ERR_UNKNOWN] = ": unknown error"
	};

	if (err < 0 || err >= ERR_COUNT)
		return (info[ERR_UNKNOWN]);
	return (info[err]);
}

/**
 * @brief Constructs the context portion of the error message.
 *
 * @param buf Buffer to store the constructed context
 * @param ctx The context of the error (builtin name and subject)
 * @return The size of the constructed context.
 */
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

/**
 * @brief Constructs the complete error message including context and error
 * information.
 *
 * @param buf Buffer to store the constructed error message
 * @param err The error code
 * @param ctx The context of the error (builtin name and subject)
 * @return The size of the constructed error message.
 */
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

/**
 * @brief Creates a context structure for error handling.
 *
 * @param builtin The name of the built-in command
 * @param subject The subject related to the error (can be NULL)
 * @return The constructed context structure.
 */
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

/**
 * @brief Handles built-in command errors by printing appropriate messages.
 *
 * @param ctx The context of the error (builtin name and subject)
 * @param err The error code
 * @param int_code The integer code to return
 * @return The provided integer code.
 */
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
