/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 22:10:09 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 18:38:21 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "builtins/builtins.h"
#include "builtins/echo_internal.h"
#include "core/string.h"

#define FLAG_N		1
#define FLAG_E		2
#define FLAG_S		4

#define BUF_SIZE	4096

/**
 * @brief Parses the command-line options and gets the corresponding flags.
 *
 * @param opt The command-line option string
 * @param flags Pointer to the flags variable to be updated
 * @return true if valid flags were found, false otherwise
 */
static bool	get_flags(const char *opt, char *flags)
{
	int		i;
	char	curr;

	if (!opt || opt[0] != '-' || ft_strcmp(opt, "-") == 0)
		return (false);
	curr = *flags;
	i = 1;
	while (opt[i])
	{
		if (opt[i] == 'n')
			*flags |= FLAG_N;
		else if (opt[i] == 'e')
			*flags |= FLAG_E;
		else if (opt[i] == 'E')
			*flags &= ~FLAG_E;
		else if (opt[i] == 's')
			*flags |= FLAG_S;
		else
		{
			*flags = curr;
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief Sets the flags based on the command-line arguments.
 *
 * @param argv Pointer to the array of command-line arguments
 * @return The combined flags.
 */
static char	set_flags(char ***argv)
{
	char	flags;

	flags = 0;
	while (*argv[0])
	{
		if (ft_strcmp(*argv[0], "--") == 0)
		{
			(*argv)++;
			break ;
		}
		if (!get_flags(*argv[0], &flags))
			break ;
		(*argv)++;
	}
	return (flags);
}

/**
 * @brief Flushes the buffer to standard output.
 *
 * @param buf The buffer to flush
 * @param ptr Pointer to the current position in the buffer
 */
static void	flush_buffer(char *buf, char **ptr)
{
	if (*ptr > buf)
	{
		write(1, buf, (size_t)(*ptr - buf));
		*ptr = buf;
	}
}

/**
 * @brief Fills the buffer with the given source string, handling escape
 * sequences if needed.
 *
 * @param src The source string to fill from
 * @param buf The buffer to fill
 * @param ptr Pointer to the current position in the buffer
 * @param flags The flags indicating how to handle escape sequences
 * @return true if an early termination escape sequence was encountered, false
 * otherwise.
 */
static bool	fill_buffer(const char *src, char *buf, char **ptr, char flags)
{
	int		c;

	while (*src)
	{
		if (flags & FLAG_E && *src == '\\' && *(src + 1))
		{
			src++;
			c = get_escape_char(&src);
			if (c == -1)
			{
				flush_buffer(buf, ptr);
				return (true);
			}
			**ptr = (char)c;
		}
		else
		{
			**ptr = *src;
			src++;
		}
		(*ptr)++;
		if ((size_t)(*ptr - buf) >= BUF_SIZE)
			flush_buffer(buf, ptr);
	}
	return (false);
}

/**
 * @brief Echoes the given arguments to standard output.
 *
 * @param sh Pointer to the shell structure (unused)
 * @param argc Argument count (unused)
 * @param argv Argument vector
 * @param envp Environment variables (unused)
 * @return Exit status code.
 */
int	builtin_echo(
	__attribute__((unused)) t_shell *sh,
	__attribute__((unused)) int argc,
	char **argv,
	__attribute__((unused)) char **envp)
{
	char	buf[BUF_SIZE];
	char	*ptr;
	char	flags;

	argv++;
	flags = set_flags(&argv);
	ptr = buf;
	while (*argv)
	{
		if (fill_buffer(*argv, buf, &ptr, flags))
			return (0);
		if (argv[1] && !(flags & FLAG_S))
			*ptr++ = ' ';
		flush_buffer(buf, &ptr);
		argv++;
	}
	if (!(flags & FLAG_N))
		*ptr++ = '\n';
	flush_buffer(buf, &ptr);
	return (0);
}
