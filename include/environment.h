/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:20:09 by smamalig          #+#    #+#             */
/*   Updated: 2025/08/29 07:27:07 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "libft.h"

typedef struct s_environment
{
	t_vector	public;
	t_vector	private;
}	t_environment;

t_result	environment_init(t_environment *env, char **envp);

#endif
