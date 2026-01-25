/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:20:09 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 12:03:47 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "allocator/allocator.h"
# include "core/stdlib.h"
#include <limits.h>

typedef uint8_t	t_env_flags;

# define ENV_FLAG_RDONLY    0x01
# define ENV_FLAG_EXPORT    0x02
# define ENV_FLAG_INTEGER   0x04
# define ENV_FLAG_STACK_KEY 0x08
# define ENV_FLAG_STACK     0x10

typedef struct s_env_bucket
{
	const char	*key;
	const char	*value;

	uint8_t		flags;
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

t_result		env_init(t_env *env, t_allocator *allocator, char **envp);
void			env_destroy(t_env *env);

t_result		env_set(t_env *env, const char *key, const char *value,
					t_env_flags flags);
const char		*env_get(t_env *env, const char *key);
t_result		env_remove(t_env *env, const char *key);
char			**env_build(t_env *env, t_arena *arena);

t_result		env_set_flag(t_env *env, const char *key, t_env_flags flag);
t_result		env_toggle_flag(t_env *env, const char *key, t_env_flags flag);
t_result		env_clear_flag(t_env *env, const char *key, t_env_flags flag);
bool			env_exists(t_env *env, const char *key);

// internal function, use with caution
t_env_bucket	*env_find_key(t_env *env, const char *key);

#endif // ENV_H
