/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 22:10:09 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 11:36:26 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "builtins.h"
#include "libft.h"

#define FLAG_N		1
#define FLAG_E		2
#define FLAG_S		4

#define BUF_SIZE	4096

static int	get_escape_octal(const char **s)
{
	int		i;
	int		val;

	if (!*s)
		return (0);
	if (**s != '0')
		return (**s);
	val = 0;
	i = 0;
	while (i < 3 && **s && **s >= '0' && **s <= '7')
	{
		val = val * 8 + (**s - '0');
		(*s)++;
	}
	return (val);
}

static int	get_escape_hex(const char **s)
{
	int		i;
	int		val;

	if (!*s)
		return (0);
	if (**s != 'x')
		return (**s);
	val = 0;
	i = 0;
	while (i < 2 && **s && ((**s >= '0' && **s <= '9')
			|| (**s >= 'a' && **s <= 'f')
			|| (**s >= 'A' && **s <= 'F')))
	{
		if (**s >= '0' && **s <= '9')
			val = val * 16 + (**s - '0');
		else if (**s >= 'a' && **s <= 'f')
			val = val * 16 + (**s - 'a' + 10);
		else if (**s >= 'A' && **s <= 'F')
			val = val * 16 + (**s - 'A' + 10);
		i++;
	}
	return (val);
}

static int	get_escape_char(const char **s)
{
	if (**s == 'a')
		return ('\a');
	else if (**s == 'b')
		return ('\b');
	else if (**s == 'c')
		return (-1);
	else if (**s == 'e')
		return ('\033');
	else if (**s == 'f')
		return ('\f');
	else if (**s == 'n')
		return ('\n');
	else if (**s == 'r')
		return ('\r');
	else if (**s == 't')
		return ('\t');
	else if (**s == 'v')
		return ('\v');
	else if (**s == '\\')
		return ('\\');
	else if (**s == '0')
		return (get_escape_octal(s));
	else if (**s == 'x')
		return (get_escape_hex(s));
	return (**s);
}

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

static void	flush_full_buffer(char *buf, char **ptr)
{
	if ((size_t)(*ptr - buf) >= BUF_SIZE)
	{
		write(1, buf, BUF_SIZE);
		*ptr = buf;
	}
}

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
				return (true);
			**ptr = (char)c;
		}
		else
		{
			**ptr = *src;
			src++;
		}
		(*ptr)++;
		flush_full_buffer(buf, ptr);
	}
	return (false);
}

int	builtin_echo(t_shell *sh, int argc, char **argv, char **envp)
{
	char	buf[BUF_SIZE];
	char	*ptr;
	char	flags;
	bool	stop;

	(void)envp;
	(void)sh;
	(void)argc;
	argv++;
	flags = set_flags(&argv);
	ptr = buf;
	stop = 0;
	while (*argv)
	{
		stop = fill_buffer(*argv, buf, &ptr, flags);
		if (stop)
			break ;
		if (!stop && argv[1] && !(flags & FLAG_S))
			*ptr++ = ' ';
		flush_full_buffer(buf, &ptr);
		argv++;
	}
	if (!stop && !(flags & FLAG_N))
		*ptr++ = '\n';
	if (ptr > buf)
		write(1, buf, (size_t)(ptr - buf));
	return (0);
}
