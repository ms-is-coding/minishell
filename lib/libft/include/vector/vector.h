/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:41:34 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/12 16:47:59 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_vec	t_vec;

typedef enum e_vec_result
{
	VEC_OK = 0,
	VEC_OOM,
	VEC_ERR_BOUNDS,
	VEC_ERR_RDONLY,
	VEC_ERR_UNKNOWN
}	t_vec_result;

t_vec			*vec_new(size_t initial_capacity)
				__attribute__((__warn_unused_result__));
void			vec_free(t_vec *vec);
t_vec_result	vec_reserve(t_vec *v, size_t capacity);

size_t			vec_length(const t_vec *v);
size_t			vec_capacity(const t_vec *v);

void			*vec_get(const t_vec *v, ssize_t idx);
t_vec_result	vec_set(t_vec *v, size_t idx, void *value);

t_vec_result	vec_push(t_vec *v, void *value);
t_vec_result	vec_insert(t_vec *v, size_t idx, void *value);

void			*vec_pop(t_vec *v);
void			*vec_remove(t_vec *v, size_t index);

void			vec_clear(t_vec *v);

void			vec_foreach(t_vec *v,
					void (*fn)(size_t index, void *value, void *userdata),
					void *userdata);

void			vec_map(t_vec *v,
					void *(*fn)(size_t index, void *value, void *userdata),
					void *userdata);

bool			vec_every(t_vec *v,
					bool (*fn)(size_t index, void *value, void *userdata),
					void *userdata);

bool			vec_some(t_vec *v,
					bool (*fn)(size_t index, void *value, void *userdata),
					void *userdata);

#endif // VECTOR_H
