/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slab_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:59:05 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/03 00:36:59 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLAB_INTERNAL_H
# define SLAB_INTERNAL_H

# include <stdbool.h>
# include <stdint.h>

# define SLAB_FLAG_FREE 0x8000
# define SLAB_FLAG_PREV_FREE 0x4000
# define SLAB_PREV_SIZE_MASK 0x3fff

typedef struct s_slab_meta
{
	uint16_t	size;
	uint16_t	prev_block;
}	t_slab_meta;

static inline bool	is_slab_free(t_slab_meta *meta)
{
	return (!!(meta->prev_block & SLAB_FLAG_FREE));
}

static inline bool	is_prev_slab_free(t_slab_meta *meta)
{
	return (!!(meta->prev_block & SLAB_FLAG_PREV_FREE));
}

static inline uint16_t	prev_slab_size(t_slab_meta *meta)
{
	return (meta->prev_block & SLAB_PREV_SIZE_MASK);
}

#endif
