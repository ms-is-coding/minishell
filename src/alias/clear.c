/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:08:52 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/11 17:55:13 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "alias/alias_internal.h"
#include "libft.h"

void	alias_clear(t_alias *alias)
{
	size_t	i;

	i = 0;
	while (i < alias->capacity)
		ft_memset(&alias->buckets[i++], 0, sizeof(t_alias_bucket));
}
