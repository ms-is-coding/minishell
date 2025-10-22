/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:33:22 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/22 19:41:21 by macarnie         ###   ########.fr       */
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
		return ((*s)++, '\a');
	else if (**s == 'b')
		return ((*s)++, '\b');
	else if (**s == 'c')
		return ((*s)++, -1);
	else if (**s == 'e')
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
