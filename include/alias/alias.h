/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:20:09 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/09 14:43:15 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

# include "allocator/allocator.h"
# include "libft.h"

typedef struct s_alias_bucket
{
	const char	*key;
	const char	*value;
	bool		is_tombstone;

	char		reserved[6];
}	t_alias_bucket;

typedef struct s_alias
{
	t_allocator		*allocator;
	t_alias_bucket	*buckets;
	size_t			count;
	size_t			capacity;
}	t_alias;

t_result	alias_init(t_alias *alias, t_allocator *allocator);
void		alias_destroy(t_alias *alias);

t_result	alias_set(t_alias *alias, const char *key, const char *value);
const char	*alias_get(t_alias *alias, const char *key);
void		alias_remove(t_alias *alias, const char *key);

#endif // ALIAS_H
