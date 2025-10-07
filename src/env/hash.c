/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:30:51 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/06 00:39:44 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env_internal.h"
#include <stddef.h>

#if UINTPTR_MAX == 0xFFFFFFFF

size_t	env_hash(t_env *env, const char *data)
{
	size_t	hash;

	hash = 0x811c9dc5ul;
	while (*data)
	{
		hash *= 0x01000193ul;
		hash ^= (size_t)(*data);
		data++;
	}
	return (hash % env->capacity);
}

#elif UINTPTR_MAX == 0xFFFFFFFFFFFFFFFFu

size_t	env_hash(t_env *env, const char *data)
{
	size_t	hash;

	hash = 0xcbf29ce484222325ull;
	while (*data)
	{
		hash *= 0x00000100000001b3ull;
		hash ^= (size_t)(*data);
		data++;
	}
	return (hash % env->capacity);
}

#else
# error "Unsupported architecture"
#endif
