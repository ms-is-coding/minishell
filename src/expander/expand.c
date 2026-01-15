/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:33:24 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/15 11:56:05 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include "expander/expander.h"
#include "expander/expander_internal.h"
#include "core/string.h"

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
static void	expander_wildcard(t_expander *exp, t_var_expansion_mode mode)
{
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir(".");
	while (my_readdir(dir, &dirent))
	{
		if (dirent->d_name[0] == '.')
			continue ;
		if (mode == VEXPM_PREPARE)
		{
			exp->len = ft_strlen(dirent->d_name);
			expander_var_extract(exp, mode);
			ft_strlcpy(exp->frame->argv[exp->frame->argc - 1],
				dirent->d_name, 256);
		}
		else
			exp->frame->argc++;
	}
	if (mode == VEXPM_PREPARE)
		exp->frame->argc = exp->prev_argc;
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
	exp->force_extract = false;
	if (mode == VEXPM_PREPARE)
		exp->prev_argc = exp->frame->argc;
	if (exp->next_char == '~')
		expander_user(exp, mode);
	if (exp->next_char == '*')
		return (expander_wildcard(exp, mode));
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
	if (exp->len > 0 || exp->force_extract)
		expander_var_extract(exp, mode);
	if (mode == VEXPM_PREPARE)
		exp->frame->argc = exp->prev_argc;
}
