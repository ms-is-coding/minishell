/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:04:43 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 15:30:17 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"
/**
 * @brief Creates a new arena by allocating memory for it.
 *
 * @param alc Pointer to the allocator structure
 * @return Pointer to the newly created arena, or NULL on failure.
 * @note this function assumes allocator_alloc will fallback to malloc.
 */
t_arena	*allocator_arena_create(t_allocator *alc)
{
	return (allocator_alloc(alc, sizeof(t_arena), NULL).data);
}
