/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:42:44 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 16:19:18 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander.h"
#include "expander/expander_internal.h"
#include "util/exec.h"
#include "util/help.h"
#include "shell.h"
#include "core/string.h"
#include "core/stdio.h"

/**
 * @brief Extracts the username from the expander's next characters.
 * @param exp Pointer to the expander
 * @return Pointer to the extracted username, or NULL if no username is found.
 */
static char	*extract_user(t_expander *exp)
{
	static char	user[256];
	size_t		u;

	u = 0;
	if (!exp->next_char || exp->next_char == '/')
		return (NULL);
	while (exp->next_char && u < sizeof(user) - 1
		&& (exp->next_char != '/'))
		user[u++] = expander_next(exp);
	user[u] = '\0';
	return (user);
}

/**
 * @brief Extracts the home directory of a given user using the getent command.
 *
 * @param user The username whose home directory is to be extracted
 * @return Pointer to the home directory string, or NULL if not found.
 */
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

/**
 * @brief Retrieves the home directory of a specified user and updates the
 * expander.
 *
 * @param exp Pointer to the expander
 * @param user The username whose home directory is to be retrieved
 * @param mode The variable expansion mode
 */
static void	get_user_home(t_expander *exp, const char *user,
				t_var_expansion_mode mode)
{
	const char	*home;

	home = extract_home(user);
	if (!home)
	{
		exp->len += 1 + ft_strlen(user);
		if (mode == VEXPM_EXTRACT)
			ft_sprintf(exp->frame->argv[exp->frame->argc], "%s~%s",
				exp->frame->argv[exp->frame->argc], user);
		return ;
	}
	exp->len += ft_strlen(home);
	if (mode == VEXPM_EXTRACT)
		ft_strcat(exp->frame->argv[exp->frame->argc], home);
	ft_free((void *)(intptr_t)home);
}

/**
 * @brief Retrieves the home directory of the current user and updates the
 * expander. Also sets the HOME environment variable.
 *
 * @param exp Pointer to the expander
 * @param mode The variable expansion mode
 */
static void	get_self_home(t_expander *exp, t_var_expansion_mode mode)
{
	const char	*home;

	help_warn(HELP_HOME_EXPAND);
	home = extract_home(env_get(&((t_shell *)exp->sh)->env, "UID"));
	if (!home)
		return ;
	exp->len += ft_strlen(home);
	if (mode == VEXPM_EXTRACT)
		ft_strcat(exp->frame->argv[exp->frame->argc], home);
	home = allocator_strdup(home);
	if (!home)
		return ;
	env_set(&((t_shell *)exp->sh)->env, "HOME", home,
		ENV_FLAG_EXPORT | ENV_FLAG_STACK_KEY);
}

/**
 * @brief Expands the user home directory in the expander.
 *
 * @param exp Pointer to the expander
 * @param mode The variable expansion mode
 */
void	expander_user(t_expander *exp, t_var_expansion_mode mode)
{
	t_shell		*sh;
	const char	*home;
	const char	*user;

	sh = exp->sh;
	expander_next(exp);
	user = extract_user(exp);
	home = env_get(&sh->env, "HOME");
	if (user)
		get_user_home(exp, user, mode);
	else if (!home)
		get_self_home(exp, mode);
	else
	{
		exp->len += ft_strlen(home);
		if (mode == VEXPM_EXTRACT)
			ft_strcat(exp->frame->argv[exp->frame->argc], home);
	}
}
