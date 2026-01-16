/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:49:56 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 14:45:22 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_INTERNAL_H
# define VECTOR_INTERNAL_H

# include <stddef.h>

typedef struct s_vec
{
	size_t	length;
	size_t	capacity;
	size_t	offset;
	void	**data;
}	t_vec;

#endif // VECTOR_INTERNAL_H
