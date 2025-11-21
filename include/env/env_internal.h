/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:33:01 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/21 16:54:45 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_INTERNAL_H
# define ENV_INTERNAL_H

# include "env.h"

size_t			env_hash(t_env *env, const char *data);
t_env_bucket	*env_find_empty(t_env *env, const char *key);
void			env_free_bucket(t_env_bucket *bucket);
t_result		env_resize(t_env *env);

#endif // ENV_INTERNAL_H
