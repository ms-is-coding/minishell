/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 10:07:55 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 18:39:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_INTERNAL_H
# define ALLOCATOR_INTERNAL_H

# include "allocator.h"
# include <stdbool.h>

# define ARENA_FLAG_LARGE 0x8000
# define ARENA_FLAG_ACTIVE 0x4000
# define ARENA_ID_MASK 0x3fff

t_allocator		*get_allocator(t_allocator *alc)
				__attribute__((__warn_unused_result__));

t_arena			*allocator_arena_create(t_allocator *alc);
t_arena			*allocator_arena_find(t_allocator *alc, t_arena_id id);
void			allocator_arena_destroy(t_allocator *alc,
					t_arena *arena);

t_allocation	allocator_arena_alloc(t_allocator *alc, t_arena *arena,
					size_t size);

t_slab_region	*allocator_slab_create(t_allocator *alc);
void			allocator_slab_destroy(t_allocator *alc,
					t_slab_region *slab);

t_allocation	allocator_slab_alloc(t_allocator *alc, size_t size);
void			allocator_slab_free(t_allocation alloc);

__attribute__((__always_inline__))
static inline bool	is_arena(t_arena *arena)
{
	return (!(arena->id & ARENA_FLAG_LARGE));
}

__attribute__((__always_inline__))
static inline bool	is_arena_active(t_arena *arena)
{
	return (arena->id & ARENA_FLAG_ACTIVE);
}

__attribute__((__always_inline__))
static inline t_arena_id	real_arena_id(t_arena *arena)
{
	return (arena->id & ARENA_ID_MASK);
}

#endif // ALLOCATOR_INTERNAL_H
