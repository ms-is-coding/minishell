/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:20:09 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 16:57:19 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include "libft.h"

typedef struct s_environ
{
	t_vector	public;
	t_vector	private;
}	t_environ;

t_result	environ_init(t_environ *env, char **envp);

#endif // ENVIRON_H
