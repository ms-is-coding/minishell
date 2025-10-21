/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:25:19 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/20 16:39:04 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander_internal.h"
#include "libft.h"
#include "shell.h"
#include <stdlib.h>

// $VERSION
// $TRASH_VERSION ?
// $?
// $$
// $RANDOM
// others TBD
// regular variables

#include "libft.h"

static const char	*extract_var(t_expander *exp)
{
	char		key[256];
	size_t		k;

	k = 0;
	while (exp->next_char && !is_var_operator(exp->next_char)
		&& k < sizeof(key) - 1)
		key[k++] = expander_next(exp);
	key[k] = '\0';
	if (ft_strcmp("?", key) == 0)
		return (ft_itoa_unsafe(ft_vector_at(&((t_shell *)exp->sh)
					->vm.exit_codes, -1).value.i32));
	return (env_get(&((t_shell *)exp->sh)->env, key));
}

void	expander_var_no_ifs(t_expander *exp, bool dry_run)
{
	const char	*value;

	value = extract_var(exp);
	if (!value)
		return ;
	if (!dry_run)
		ft_strcat(exp->frame->argv[exp->frame->argc], value);
	exp->len += ft_strlen(value);
}

void	expander_var_extract(t_expander *exp, t_var_expansion_mode mode)
{
	t_allocator	*alc;

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
