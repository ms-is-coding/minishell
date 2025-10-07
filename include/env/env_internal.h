/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:33:01 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/06 00:57:10 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_INTERNAL_H
# define ENV_INTERNAL_H

# include "env.h"

size_t			env_hash(t_env *env, const char *data);
t_env_bucket	*env_find_key(t_env *env, const char *key);
t_env_bucket	*env_find_empty(t_env *env, const char *key);

#endif // ENV_INTERNAL_H
