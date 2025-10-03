/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_mal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:39:54 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/03 10:25:56 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "builtins.h"
#include "libft.h"

#define FLAG_N	1
#define FLAG_E	2
#define FLAG_S	4

static int	get_escape_octal(const char *s, int *i)
{
	int	j;
	int	val;

	if (s[*i] != '0')
		return (s[*i]);
	(*i)++;
	val = 0;
	j = 0;
	while (j < 3 && s[*i] >= '0' && s[*i] <= '7')
	{
		val = val * 8 + (s[*i] - '0');
		(*i)++;
		j++;
	}
	return (val);
}

static int	get_escape_hex(const char *s, int *i)
{
	int	j;
	int	val;

	if (s[*i] != 'x')
		return (s[*i]);
	(*i)++;
	val = 0;
	j = 0;
	while (j < 2 && ((s[*i] >= '0' && s[*i] <= '9')
			|| (s[*i] >= 'a' && s[*i] <= 'f')
			|| (s[*i] >= 'A' && s[*i] <= 'F')))
	{
		if (s[*i] >= '0' && s[*i] <= '9')
			val = val * 16 + (s[*i] - '0');
		else if (s[*i] >= 'a' && s[*i] <= 'f')
			val = val * 16 + (s[*i] - 'a' + 10);
		else if (s[*i] >= 'A' && s[*i] <= 'F')
			val = val * 16 + (s[*i] - 'A' + 10);
		(*i)++;
		j++;
	}
	return (val);
}

static int	get_escape_char(const char *s, int *i)
{
	if (s[*i] == 'a')
		return ('\a');
	else if (s[*i] == 'b')
		return ('\b');
	else if (s[*i] == 'c')
		return (-1);
	else if (s[*i] == 'e')
		return ('\033');
	else if (s[*i] == 'f')
		return ('\f');
	else if (s[*i] == 'n')
		return ('\n');
	else if (s[*i] == 'r')
		return ('\r');
	else if (s[*i] == 't')
		return ('\t');
	else if (s[*i] == 'v')
		return ('\v');
	else if (s[*i] == '\\')
		return ('\\');
	else if (s[*i] == '0')
		return (get_escape_octal(s, i));
	else if (s[*i] == 'x')
		return (get_escape_hex(s, i));
	return (s[*i]);
}

static size_t	escape_strlen(const char *s)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1])
		{
			i++;
			if (get_escape_char(s, &i) == 0)
				break ;
		}
		size++;
		i++;
	}
	return (size);
}

static char	*escape_strcpy(char *dst, const char *src, bool *stop)
{
	char	*ptr;
	int		c;
	int		i;

	ptr = dst;
	i = 0;
	while (src[i])
	{
		if (src[i] == '\\' && src[i + 1])
		{
			i++;
			c = get_escape_char(src, &i);
			if (c == -1)
				*stop = true;
			if (c == 0 || c == -1)
				break ;
			*ptr++ = (char)c;
		}
		else
			*ptr++ = src[i];
		i++;
	}
	*ptr = '\0';
	return (ptr);
}

static bool	get_flags(const char *opt, char *flags)
{
	int		i;
	char	curr;

	if (!opt || opt[0] != '-')
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

static char	set_flags(int *argc, char ***argv)
{
	char	flags;

	if (*argc < 2)
		return (0);
	flags = 0;
	while (*argc > 1)
	{
		if (ft_strcmp(**argv, "--") == 0)
		{
			*argc -= 1;
			*argv += 1;
			break ;
		}
		if (!get_flags(**argv, &flags))
			break ;
		*argc -= 1;
		*argv += 1;
	}
	return (flags);
}

static size_t	get_echo_len(int argc, char **argv, char flags)
{
	size_t	size;
	int		i;

	size = 0;
	i = 1;
	while (i < argc)
	{
		if (flags & FLAG_E)
			size += escape_strlen(argv[i]);
		else
			size += ft_strlen(argv[i]);
		if (i + 1 < argc && !(flags & FLAG_S))
			size += 1;
		i++;
	}
	if (!(flags & FLAG_N))
		size += 1;
	return (size);
}

static void	swrite_echo(int argc, char **argv, char flags, char *str)
{
	char	*ptr;
	int		i;
	bool	stop;

	i = 1;
	ptr = str;
	stop = false;
	while (i < argc)
	{
		if (flags & FLAG_E)
			ptr = escape_strcpy(ptr, argv[i], &stop);
		else
			ptr = ft_strcpy(ptr, argv[i]);
		if (stop == true)
			break ;
		if (i + 1 < argc && !(flags & FLAG_S))
			*ptr++ = ' ';
		i++;
	}
	if (!(flags & FLAG_N) && stop == false)
		*ptr++ = '\n';
	*ptr = '\0';
}

int	builtin_echo(t_shell *sh, int argc, char **argv)
{
	char	flags;
	char	*str;
	size_t	len;

	(void)sh;
	flags = set_flags(&argc, &argv);
	len = get_echo_len(argc, argv, flags);
	str = malloc(len + 1);
	if (!str)
		return (1);
	swrite_echo(argc, argv, flags, str);
	write(1, str, len);
	free(str);
	return (0);
}
