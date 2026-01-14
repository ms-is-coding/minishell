/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:30:51 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 15:47:13 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env_internal.h"
#include <stddef.h>

#if UINTPTR_MAX == 0xFFFFFFFF

/**
 * @brief Computes the hash value for a given string using the FNV-1a algorithm.
 *
 * @param env Pointer to the environment structure
 * @param data The string to hash
 * @return The computed hash value modulo the environment's capacity.
 * @note This implementation is for 32-bit architectures.
 */
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

/**
 * @brief Computes the hash value for a given string using the FNV-1a algorithm.
 *
 * @param env Pointer to the environment structure
 * @param data The string to hash
 * @return The computed hash value modulo the environment's capacity.
 * @note This implementation is for 64-bit architectures.
 */
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
