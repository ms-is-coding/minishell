/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:20:09 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/17 09:50:37 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "allocator/allocator.h"
# include "libft.h"

typedef struct s_env_bucket
{
	const char	*key;
	const char	*value;
	bool		is_public;
	bool		is_tombstone;

	char		reserved[6];
}	t_env_bucket;

typedef struct s_env
{
	t_allocator		*allocator;
	t_env_bucket	*buckets;
	size_t			count;
	size_t			capacity;
}	t_env;

t_result	env_init(t_env *env, t_allocator *allocator, char **envp);
void		env_destroy(t_env *env);

t_result	env_set(t_env *env, const char *key, const char *value,
				bool is_public);
const char	*env_get(t_env *env, const char *key);
t_result	env_remove(t_env *env, const char *key);
char		**env_build(t_env *env, t_arena *arena);

#endif // ENV_H
