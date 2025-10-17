/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:12:11 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/17 02:42:38 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_INTERNAL_H
# define EXPANDER_INTERNAL_H

# include "expander/expander.h"
# include <stddef.h>

bool	is_var_operator(char sc);
bool	dquote_escape(char c);

void	expander_setup(t_expander *exp, t_exec_frame *frame,
			const char *arg, size_t len);
char	expander_next(t_expander *exp);

void	expander_var_no_ifs(t_expander *exp, bool dry_run);
void	expander_squote(t_expander *exp, bool dry_run);
void	expander_dquote(t_expander *exp, bool dry_run);
void	expander_char(t_expander *exp, bool dry_run);
void	expander_user(t_expander *exp, bool dry_run);

void	expander_var(t_expander *exp, t_var_expansion_mode mode);
void	expander_var_extract(t_expander *exp, t_var_expansion_mode mode);

#endif // EXPANDER_INTERNAL_H
