/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:33:01 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 17:23:21 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_INTERNAL_H
# define ALIAS_INTERNAL_H

# include "alias.h"

size_t			alias_hash(t_alias *alias, const char *data);
t_alias_bucket	*alias_find_key(t_alias *alias, const char *key);
t_alias_bucket	*alias_find_empty(t_alias *alias, const char *key);

#endif // ALIAS_INTERNAL_H
