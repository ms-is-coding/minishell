/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:42:44 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/21 23:36:35 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander_internal.h"
#include "exec/exec.h"
#include "help/help.h"
#include "shell.h"

static char	*extract_user(t_expander *exp)
{
	static char	user[256];
	size_t		u;

	u = 0;
	if (!(ft_islower(exp->next_char)
			|| exp->next_char == '-'
			|| exp->next_char == '_'))
		return (NULL);
	while (exp->next_char && u < sizeof(user) - 1
		&& (ft_islower(exp->next_char)
			|| exp->next_char == '-'
			|| exp->next_char == '_'))
		user[u++] = expander_next(exp);
	user[u] = '\0';
	return (user);
}

static const char	*extract_home(const char *user)
{
	const char	*str;
	int			i;

	str = exec_with_output((char *[]){
			(char *)(intptr_t)"/usr/bin/getent",
			(char *)(intptr_t)"passwd",
			(char *)(intptr_t)user, NULL});
	if (!str)
		return (NULL);
	i = 0;
	while (i < 5)
	{
		str = ft_strchr(str, ':');
		if (str == NULL)
			return (NULL);
		str++;
		i++;
	}
	if (ft_strchr(str, ':'))
		ft_strchr(str, ':')[0] = '\0';
	return (str);
}

static void	get_user_home(t_expander *exp, const char *user, bool dry_run)
{
	const char	*home;

	home = extract_home(user);
	if (!home)
	{
		exp->len += 1 + ft_strlen(user);
		if (!dry_run)
			ft_sprintf(exp->frame->argv[exp->frame->argc], "%s~%s",
				exp->frame->argv[exp->frame->argc], user);
		return ;
	}
	exp->len += ft_strlen(home);
	if (!dry_run)
		ft_strcat(exp->frame->argv[exp->frame->argc], home);
}

static void	get_self_home(t_expander *exp, bool dry_run)
{
	const char	*home;

	help_warn(HELP_HOME_EXPAND);
	home = extract_home(env_get(&((t_shell *)exp->sh)->env, "UID"));
	if (!home)
		return ;
	exp->len += ft_strlen(home);
	if (!dry_run)
		ft_strcat(exp->frame->argv[exp->frame->argc], home);
	env_set(&((t_shell *)exp->sh)->env, "HOME", home, ENV_FLAG_EXPORT);
}

void	expander_user(t_expander *exp, bool dry_run)
{
	t_shell		*sh;
	const char	*home;
	const char	*user;

	sh = exp->sh;
	expander_next(exp);
	user = extract_user(exp);
	home = env_get(&sh->env, "HOME");
	if (user)
		get_user_home(exp, user, dry_run);
	else if (!home)
		get_self_home(exp, dry_run);
	else
	{
		exp->len += ft_strlen(home);
		if (!dry_run)
			ft_strcat(exp->frame->argv[exp->frame->argc], home);
	}
}
