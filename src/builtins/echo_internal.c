/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:33:22 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/18 18:33:30 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	get_escape_char(const char **s)
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
