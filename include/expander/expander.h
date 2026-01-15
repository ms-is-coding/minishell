/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:25:47 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 14:47:24 by smamalig         ###   ########.fr       */
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
	const char		*ifs;
	size_t			arg_len;
	size_t			len;
	size_t			i;

	int				prev_argc;

	char			curr_char;
	char			next_char;
	bool			end;
	bool			force_extract;
}	t_expander;

typedef enum e_var_expansion_mode
{
	VEXPM_COUNT,
	VEXPM_PREPARE,
	VEXPM_EXTRACT
}	t_var_expansion_mode;

void	expander_init(t_expander *exp, void *sh);
void	expander_setup(t_expander *exp, t_exec_frame *frame,
			const char *arg, size_t len);
void	expander_expand(t_expander *exp, t_var_expansion_mode mode);

#endif // EXPANDER_H
