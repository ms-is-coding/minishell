/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:33:24 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 16:27:27 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include <sys/types.h>
#include <dirent.h>
#include "expander/expander.h"
#include "expander/expander_internal.h"
#include "core/string.h"
#include "shell.h"

/**
 * @brief Expands quotes without variable expansion.
 *
 * @param exp Pointer to the expander
 * @param mode The variable expansion mode
 */
void	expander_expand_quotes(t_expander *exp, t_var_expansion_mode mode)
{
	while (exp->next_char)
	{
		expander_next(exp);
		if (exp->curr_char == '"')
			expander_dquote_no_var(exp, mode);
		if (exp->curr_char == '\'')
			expander_squote(exp, mode);
		else
			expander_char(exp, mode);
	}
}

__attribute__((__always_inline__))
inline bool	my_readdir(DIR *dir, struct dirent **dirent)
{
	*dirent = readdir(dir);
	if (!*dirent)
		return (false);
	return (true);
}

/**
 * @brief Expands wildcard characters in the current directory.
 *
 * @param exp Pointer to the expander
 * @param mode The variable expansion mode
 */
void	expander_wildcard(t_expander *exp, t_var_expansion_mode mode)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_allocator		*alc;

	dir = opendir(".");
	while (my_readdir(dir, &dirent))
	{
		if (dirent->d_name[0] == '.')
			continue ;
		if (mode == VEXPM_PREPARE)
		{
			alc = &((t_shell *)exp->sh)->allocator;
			exp->frame->argv[exp->frame->argc]
				= allocator_alloc(alc, dirent->d_reclen,
					exp->frame->arena).data;
			if (!exp->frame->argv[exp->frame->argc])
				return ;
			exp->frame->argv[exp->frame->argc][0] = '\0';
		}
		else if (mode == VEXPM_EXTRACT)
			ft_strlcpy(exp->frame->argv[exp->frame->argc], dirent->d_name, 256);
		exp->frame->argc++;
	}
	closedir(dir);
}
 /**
 * @brief Expands the input string based on the specified mode.
 *
 * @param exp Pointer to the expander structure
 * @param mode The variable expansion mode
 */
void	expander_expand(t_expander *exp, t_var_expansion_mode mode)
{
	int	prev_argc;

	if (mode == VEXPM_PREPARE)
		prev_argc = exp->frame->argc;
	if (exp->next_char == '~')
		expander_user(exp, mode);
	if (exp->next_char == '*')
	{
		expander_next(exp);
		expander_wildcard(exp, mode);
	}
	while (exp->next_char)
	{
		expander_next(exp);
		if (exp->curr_char == '$')
			expander_var(exp, mode);
		else if (exp->curr_char == '"')
			expander_dquote(exp, mode);
		else if (exp->curr_char == '\'')
			expander_squote(exp, mode);
		else
			expander_char(exp, mode);
	}
	expander_var_extract(exp, mode);
	if (mode == VEXPM_PREPARE)
		exp->frame->argc = prev_argc;
}
