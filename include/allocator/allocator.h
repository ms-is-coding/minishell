/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 10:07:04 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/03 20:40:36 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_H
# define ALLOCATOR_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>

# ifndef STACK_ARENAS
#  define STACK_ARENAS 0
# endif
# ifndef STACK_SLABS
#  define STACK_SLABS 0
# endif
# ifndef MAX_ALLOC_SIZE
#  define MAX_ALLOC_SIZE 512
# endif

# ifdef STACK_ONLY
#  define ARENA_CAPACITY 4080 // 4096 - 16
#  define SLAB_CAPACITY 4080 // 4096 - 16
# else // add malloc padding
#  define ARENA_CAPACITY 4072 // 4096 - 16 - 8
#  define SLAB_CAPACITY 4072 // 4096 - 16 - 8
# endif

typedef uint16_t	t_arena_id;

typedef enum e_alloc_kind
{
	ALLOC_ARENA,
	ALLOC_SLAB,
	ALLOC_HEAP,
}	t_alloc_kind;

typedef struct s_allocation
{
	void			*region;
	void			*data;
	size_t			size;
	t_alloc_kind	kind;
	uint16_t		parent_id;
	char			reserved[2];
}	t_allocation;

typedef struct s_arena
{
	struct s_arena	*next;
	uint16_t		id;
	uint16_t		flags;
	uint16_t		used;
	char			reserved[2];
	char			data[ARENA_CAPACITY];
}	t_arena;

typedef struct s_large_alloc
{
	struct s_arena	*next;
	uint16_t		id;
	uint16_t		flags;
	char			reserved[4];
	void			*data;
}	t_large_alloc;

typedef struct s_slab_region
{
	struct s_slab_region	*next;
	uint16_t				id;
	uint16_t				used;
	uint16_t				max_free;
	char					reserved[2];
	char					data[SLAB_CAPACITY];
}	t_slab_region;

typedef struct s_allocator
{
	t_arena			*arenas;
	t_slab_region	*slabs;
	t_arena_id		next_arena_id;
	uint16_t		next_slab_id;
	char			reserved[4];
	t_arena			stack_arenas[STACK_ARENAS];
	t_slab_region	stack_slabs[STACK_SLABS];
}	t_allocator;

void			allocator_init(t_allocator *alc);
void			allocator_destroy(t_allocator *alc);

t_arena			*allocator_arena_new(t_allocator *alc);
void			allocator_arena_free(t_allocator *alc, t_arena *arena);

t_allocation	allocator_alloc(t_allocator *alc, size_t size, t_arena *arena);
void			allocator_free(t_allocator *alc, t_allocation alloc);

#endif // ALLOCATOR_H
