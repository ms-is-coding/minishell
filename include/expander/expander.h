/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:25:47 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/11 16:24:25 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "vm/vm.h"
# include <stddef.h>

typedef struct s_expander
{
	void			*sh;
	t_exec_frame	*frame;
	const char		*arg;
	size_t			len;
}	t_expander;

void	expander_init(t_expander *exp, void *sh);
void	expander_expand(t_expander *exp, t_exec_frame *frame,
			const char *arg, size_t len);

#endif // EXPANDER_H
