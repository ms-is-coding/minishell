/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 23:33:00 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 15:58:22 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "magic.h"
#include "core/string.h"

static	int	run_check(const char *s, size_t *i_ptr)
{
	int	i;

	i = -1;
	while (++i < NBYTES)
	{
		if (s[i] == '\0')
			return (1);
		(*i_ptr)++;
	}
	return (0);
}

__attribute__((no_sanitize_address))
size_t	ft_strlen(const char *s)
{
	const uintptr_t	*fast;
	size_t			i;
	uintptr_t		value;

	i = 0;
	while ((uintptr_t)(s + i) & ALIGN_MASK)
	{
		if (s[i] == '\0')
			return (i);
		i++;
	}
	fast = (const uintptr_t *)(const void *)(s + i);
	while (1)
	{
		value = *fast++;
		if (((value - STRLEN_LOMAGIC) & ~value & STRLEN_HIMAGIC) != 0
			&& run_check((const char *)(fast - 1), &i))
			return (i);
		i += NBYTES;
	}
}
