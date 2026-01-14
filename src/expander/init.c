/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:13:25 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 15:48:33 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander_internal.h"
#include "shell.h"

/**
 * @brief Initializes the expander structure.
 *
 * @param exp Pointer to the expander structure
 * @param sh Pointer to the shell structure
 */
void	expander_init(t_expander *exp, void *sh)
{
	exp->sh = sh;
}

/**
 * @brief Sets up the expander for a new argument.
 *
 * @param exp Pointer to the expander structure
 * @param frame Pointer to the execution frame
 * @param arg The argument string to expand
 * @param len The length of the argument string
 */
void	expander_setup(
	t_expander *exp,
	t_exec_frame *frame,
	const char *arg,
	size_t len)
{
	exp->frame = frame;
	exp->arg = arg;
	exp->arg_len = len;
	exp->i = 1;
	exp->curr_char = '\0';
	exp->next_char = arg[0];
	exp->end = false;
	exp->ifs = env_get(&((t_shell *)exp->sh)->env, "IFS");
	if (!exp->ifs)
		exp->ifs = " \t\n";
	exp->len = 0;
}
