/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_internal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:20:15 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/10/30 21:33:50 by smamalig         ###   ########.fr       */
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

void	separate_export(char *arg, char **key, char **value)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		*eq = '\0';
	else
		*value = NULL;
	*key = ft_strdup(arg);
	if (eq)
		*value = ft_strdup(eq + 1); //no sanity checks
	else
		*value = NULL;
}
