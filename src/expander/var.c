/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:25:19 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 18:52:43 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander.h"
#include "expander/expander_internal.h"
#include "core/string.h"
#include "shell.h"
#include <stdlib.h>

/**
 * @brief Extracts the variable and retrieves its value from the environment.
 *
 * @param exp Pointer to the expander
 * @return The value of the extracted variable, or NULL if not found.
 */
static const char	*extract_var(t_expander *exp)
{
	char		key[256];
	size_t		k;

	if (exp->next_char == '?' || exp->next_char == '$' || exp->next_char == '#'
		|| (exp->next_char >= '0' && exp->next_char <= '9'))
	{
		expander_next(exp);
		if (exp->curr_char == '?')
			return (ft_itoa_unsafe((int32_t)(int64_t)
				((t_shell *)exp->sh)->vm.last_exit_code));
		if (exp->curr_char == '$')
			return (ft_itoa_unsafe(getpid()));
		return ("");
	}
	k = 0;
	while (exp->next_char && !is_var_operator(exp->next_char)
		&& k < sizeof(key) - 1)
		key[k++] = expander_next(exp);
	key[k] = '\0';
	if (k == 0)
		return (allocator_strdup("$"));
	return (env_get(&((t_shell *)exp->sh)->env, key));
}

/**
 * @brief Expands a variable without considering IFS (Internal Field Separator).
 *
 * @param exp Pointer to the expander
 * @param mode The variable expansion mode
 */
void	expander_var_no_ifs(t_expander *exp, t_var_expansion_mode mode)
{
	const char	*value;

	value = extract_var(exp);
	if (!value)
		return ;
	if (mode == VEXPM_EXTRACT)
		ft_strcat(exp->frame->argv[exp->frame->argc], value);
	exp->len += ft_strlen(value);
}

/**
 * @brief Extracts variable values considering IFS (Internal Field Separator).
 *
 * @param exp Pointer to the expander
 * @param mode The variable expansion mode
 */
void	expander_var_extract(t_expander *exp, t_var_expansion_mode mode)
{
	t_allocator	*alc;

	if (exp->len <= 0 && !exp->force_extract)
		return ;
	exp->force_extract = false;
	if (mode == VEXPM_PREPARE)
	{
		alc = &((t_shell *)exp->sh)->allocator;
		exp->frame->argv[exp->frame->argc]
			= allocator_alloc(alc, exp->len + 1, exp->frame->arena).data;
		exp->frame->argv[exp->frame->argc][0] = '\0';
	}
	exp->frame->argc++;
	exp->len = 0;
}

/**
 * @brief Expands a variable considering IFS (Internal Field Separator).
 *
 * @param exp Pointer to the expander
 * @param mode The variable expansion mode
 */
void	expander_var(t_expander *exp, t_var_expansion_mode mode)
{
	const char	*value;
	size_t		len;
	bool		has_sep;

	value = extract_var(exp);
	if (!value)
		return ;
	if (ft_strspn(value, exp->ifs))
		expander_var_extract(exp, mode);
	while (*value)
	{
		value += ft_strspn(value, exp->ifs);
		len = ft_strcspn(value, exp->ifs);
		if (!len)
			break ;
		has_sep = (value[len] && ft_strchr(exp->ifs, value[len]));
		exp->len += len;
		if (mode == VEXPM_EXTRACT)
			ft_strncat(exp->frame->argv[exp->frame->argc], value, len);
		if (has_sep)
			expander_var_extract(exp, mode);
		value += len;
	}
}
