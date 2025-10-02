/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 09:46:19 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/08 11:33:56 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_H
# define ALLOCATOR_H

# include <stddef.h>
# include <stdbool.h>

# define STACK_ARENAS 32
# define STACK_SLABS 12
# define ARENA_SIZE 4064 // 4096 - 24 - 8
# define SLAB_SIZE 4056 // 4096 - 32 - 8

typedef enum e_alloc_kind {
	ALLOC_ARENA,
	ALLOC_SLAB
}	t_alloc_kind;

typedef struct s_allocation {
	void			*region;
	void			*data;
	size_t			size;
	t_alloc_kind	kind;
}	t_allocation;

typedef struct s_arena {
	struct s_arena	*next;
	size_t			capacity;
	size_t			used;
	char			data[ARENA_SIZE];
}	t_arena;

typedef struct s_slab_block {
	struct s_slab_block	*next;
	size_t				size;
}	t_slab_block;

typedef struct s_slab_region {
	struct s_slab_region	*next;
	t_slab_block			*list;
	size_t					block_size;
	size_t					capacity;
	char					data[SLAB_SIZE];
}	t_slab_region;

typedef struct s_allocator {
	t_arena			*arenas;
	t_slab_region	*slabs;
	t_arena			stack_arenas[STACK_ARENAS];
	t_slab_region	stack_slabs[STACK_SLABS];
}	t_allocator;

void			allocator_init(t_allocator *alc);
void			allocator_destroy(t_allocator *alc);

t_arena			*allocator_arena_new(t_allocator *alc, size_t capacity);
t_allocation	allocator_arena_alloc(t_arena *arena, size_t size);
void			allocator_arena_bulk_free(t_arena *arena);

t_slab_region	*allocator_slab_new(t_allocator *allocator, size_t block_size,
					size_t num_blocks);
t_allocation	allocator_slab_alloc(t_slab_region *slab);
void			allocator_slab_free(t_allocation alloc);

t_allocation	allocator_alloc(t_allocator *alc, size_t size, bool use_slab);
void			allocator_free(t_allocation alloc);

#endif
