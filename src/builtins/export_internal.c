/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_internal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:20:15 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/11/03 14:28:33 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"
#include "libft.h"

void	print_exported(t_env *env)
{
	size_t	i;

	i = -1lu;
	while (++i < env->capacity)
	{
		if (!(env->buckets[i].flags & ENV_FLAG_EXPORT))
			continue ;
		if (env->buckets[i].key && env->buckets[i].value)
			ft_printf("export %s=\"%s\"\n",
				env->buckets[i].key, env->buckets[i].value);
		else if (env->buckets[i].key)
			ft_printf("export %s\n", env->buckets[i].key);
	}
}
