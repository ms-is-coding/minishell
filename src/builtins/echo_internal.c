/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:33:22 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/14 17:03:50 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/**
 * @brief Parses an octal escape sequence from the string.
 *
 * @param s Pointer to the string pointer
 * @return The integer value of the octal escape sequence.
 */
static int	get_escape_octal(const char **s)
{
	int		i;
	int		val;

	if (!*s)
		return (0);
	if (**s != '0')
		return (**s);
	(*s)++;
	val = 0;
	i = 0;
	while (i < 3 && **s && **s >= '0' && **s <= '7')
	{
		val = val * 8 + (**s - '0');
		(*s)++;
	}
	return (val);
}

/**
 * @brief Parses a hexadecimal escape sequence from the string.
 *
 * @param s Pointer to the string pointer
 * @return The integer value of the hexadecimal escape sequence.
 */
static int	get_escape_hex(const char **s)
{
	int		i;
	int		val;

	if (!*s)
		return (0);
	if (**s != 'x')
		return (**s);
	(*s)++;
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
		(*s)++;
		i++;
	}
	return (val);
}

/**
 * @brief Parses an escape character from the string.
 *
 * @param s Pointer to the string pointer
 * @return The integer value of the escape character.
 */
int	get_escape_char(const char **s)
{
	if (**s == 'a')
		return ((*s)++, '\a');
	else if (**s == 'b')
		return ((*s)++, '\b');
	else if (**s == 'c')
		return ((*s)++, -1);
	else if (**s == 'e' || **s == 'E')
		return ((*s)++, '\033');
	else if (**s == 'f')
		return ((*s)++, '\f');
	else if (**s == 'n')
		return ((*s)++, '\n');
	else if (**s == 'r')
		return ((*s)++, '\r');
	else if (**s == 't')
		return ((*s)++, '\t');
	else if (**s == 'v')
		return ((*s)++, '\v');
	else if (**s == '\\')
		return ((*s)++, '\\');
	else if (**s == '0')
		return (get_escape_octal(s));
	else if (**s == 'x')
		return (get_escape_hex(s));
	return (**s);
}
